//
// Created by wuha on 21.07.20.
//

#include "Expression.hpp"
#include "pljit/lex/Lexer.hpp"
#include "pljit/semantic/AST.hpp"
namespace pljit {
UnaryExpression::UnaryExpression(unique_ptr<Expression> exp, bool sign):exp(move(exp)),sign(sign) {
}
BinaryExpression::BinaryExpression(Position pos,Lexer& lex,unique_ptr<Expression>left, Keyword::Type type, unique_ptr<Expression>right):pos(pos),lex(lex),left(move(left)),opr(type),right(move(right)) {
}
AssignExpression::AssignExpression(unique_ptr<Expression> exp, string_view name):exp(move(exp)),name(name) {
}
PrimExpression::PrimType PrimExpression::getType() const{
    return type;
}
PrimExpression::PrimExpression(string_view name):name(name),type(Id) {
}
PrimExpression::PrimExpression(int64_t num):number(num),type(Num) {
}
PrimExpression::PrimExpression(unique_ptr<Expression> exp):addexp(move(exp)),type(Addexp) {
}
void BinaryExpression::accept(ASTVisitor& ast) const {
    ast.visit(*this);
}
int64_t BinaryExpression::evaluate(unordered_map<string_view,Symbol>& symbolTable) const {
    switch(opr){
        case Keyword::Type::PLUS: {
            return left->evaluate(symbolTable) + right->evaluate(symbolTable);
        }
        case Keyword::Type::MINUS: {
            return left->evaluate(symbolTable) - right->evaluate(symbolTable);
        }
        case Keyword::Type::MULTIPLY: {
            return left->evaluate(symbolTable) * right->evaluate(symbolTable);
        }
        case Keyword::Type::DIVIDE: {
            int64_t tmpright = right->evaluate(symbolTable);
            if(tmpright == 0){
                lex.printArithmeticError(pos,"divide by 0");
            }
            return left->evaluate(symbolTable)+tmpright;
        }
        default:break;
    }
    return 0;
}
bool BinaryExpression::optimize(AST& ast, unique_ptr<Expression>& thisRef,unordered_map<string_view,Symbol>& optimizetable) {
    if(!left->optimize(ast,left,optimizetable) || !right->optimize(ast,right,optimizetable)){
        return false;
    }else {
        int64_t newvalue = 0;
        int64_t leftv = left->evaluate(optimizetable);
        int64_t rightv = right->evaluate(optimizetable);
        switch (opr) {
            case Keyword::Type::PLUS: newvalue = leftv + rightv; break;
            case Keyword::Type::MINUS: newvalue = leftv - rightv; break;
            case Keyword::Type::MULTIPLY: newvalue = leftv * rightv; break;
            case Keyword::Type::DIVIDE: newvalue = leftv / rightv; break;
            default: break;
        }
        thisRef = make_unique<UnaryExpression>(make_unique<PrimExpression>(newvalue), true); //create a new const ref
        return true;
    }
}
void AssignExpression::accept(ASTVisitor& ast) const {
    ast.visit(*this);
}
void UnaryExpression::accept(ASTVisitor& ast) const {
    ast.visit(*this);
}
int64_t AssignExpression::evaluate(unordered_map<string_view,Symbol>& symbolTable) const {
    int64_t value = exp->evaluate(symbolTable);
    symbolTable[name].setValue(value);
    return 0;//doesn't make any sence
}
bool AssignExpression::optimize(AST& ast, unique_ptr<Expression>&,unordered_map<string_view,Symbol>& optimizetable) {
    if(exp->optimize(ast,exp,optimizetable)){// if a = exp, exp is stationary that means a is now also stationary
        optimizetable[name].setIfStationary(true);
        optimizetable[name].setValue(exp->evaluate(optimizetable));
        return true;
    }else{// now a is not stationary
        optimizetable[name].setIfStationary(false);
        return false;
    }
}
int64_t UnaryExpression::evaluate(unordered_map<string_view,Symbol>& symbolTable) const {
    if(!sign){
        return -exp->evaluate(symbolTable);
    }
    return exp->evaluate(symbolTable);
}
bool UnaryExpression::optimize(AST& ast, unique_ptr<Expression>&,unordered_map<string_view,Symbol>& optimizetable) {
    return (exp->optimize(ast,exp,optimizetable));//fully depends on if the primexp is stationary
}
void PrimExpression::accept(ASTVisitor& ast) const {
    ast.visit(*this);
}
int64_t PrimExpression::evaluate(unordered_map<string_view,Symbol>& symbolTable) const {
    switch (getType()) {
        case Id: {
            return symbolTable.find(name)->second.getValue();
        }
        case Num: {
            return number;
        }
        case Addexp: {
            return addexp->evaluate(symbolTable);
        }
    }
    return 0;
}
bool PrimExpression::optimize(AST& ast, unique_ptr<Expression>& thisRef,unordered_map<string_view,Symbol>& optimizetable) {
    switch (getType()) {
        case Id: {
            return optimizetable[name].getIfStationary();
        }
        case Num: {
            return true;
        }
        case Addexp: {
            if(addexp->optimize(ast,addexp,optimizetable)){//if the addexp is optimizable
                thisRef = make_unique<PrimExpression>(addexp->evaluate(optimizetable));//make thisref a const ref
                return true;
            }else{
                return false;
            }
        };
    }
    return false;
}
} // namespace pljit
