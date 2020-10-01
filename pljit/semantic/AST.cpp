//
// Created by wuha on 21.07.20.
//

#include "AST.hpp"
#include "Symbol.hpp"
#include "pljit/lex/Number.hpp"
#include "pljit/syntax/expression/Comp_Statement.hpp"
#include "pljit/syntax/expression/Function_Def.hpp"
#include "pljit/syntax/expression/Prim_Exp.hpp"
#include "pljit/syntax/expression/Statement.hpp"
#include "pljit/syntax/expression/Unary_Exp.hpp"
#include <iostream>
#include <pljit/syntax/SyntaxParser.hpp>
namespace pljit {
unique_ptr<Function> AST::analyseFuntion(Function_Def& fd) {
    unique_ptr<Function> ans = make_unique<Function>();
    if(fd.ifpara){
        for (auto& id : static_cast<Dec_List&>(*static_cast<Parameter_Dec&>(*fd.paradec).declist).children) { //iterate the parameter list
            if (id->getTokenType() == LexToken::Identifer) {//devide from ","
                string_view name = static_cast<Identifer&>(*id).getName();
                parameterlist.push_back(name);
                if (symbolTable.find(name) != symbolTable.end()) {
                    lex.printSemanticError(id->pos, name, " is declared twice");
                }
                symbolTable.insert({name, Symbol(true, Symbol::SymbolType::Para)});
            }
        }
    }
    if(fd.ifvar){
        for (auto& var : static_cast<Dec_List&>(*static_cast<Variable_Dec&>(*fd.varadec).declist).children) { //iterate the parameter list
            if (var->getTokenType() == LexToken::Identifer) {//devide from ","
                string_view name = static_cast<Identifer&>(*var).getName();
                if (symbolTable.find(name) != symbolTable.end()) {
                    lex.printSemanticError(var->pos, name, " is declared twice");
                }
                symbolTable.insert({name, Symbol(false, Symbol::SymbolType::Var)});//is not initiallized
            }
        }
    }
    if(fd.ifcon){
        for (auto& con : static_cast<Init_List&>(*static_cast<Const_Dec&>(*fd.constdec).initlist).children) { //iterate the parameter list
            if (!con->isTerminal()) {//true whrn it is "," false when it is init-declarator
                Identifer conid = static_cast<Identifer&>(*static_cast<Init_Dec&>(*con).identifer);
                string_view name = conid.getName();
                if (symbolTable.find(name) != symbolTable.end()) {
                    lex.printSemanticError(conid.pos, name, " is declared twice");
                }
                Symbol constSymbol = Symbol(true, Symbol::SymbolType::Const);
                constSymbol.setValue(static_cast<Number&>((*static_cast<Init_Dec&>(*con).literal)).getNum());//set the constvalue
                symbolTable.insert({name, constSymbol});//is initiallized
            }
        }
    }
    bool Return_Exist = false;
    for(auto& statement : static_cast<Statement_List&>(*static_cast<Comp_Statement&>(*fd.comp_states).statelist).children){//iterate over the statements
        if(!statement->isTerminal()){
            Statement& s = static_cast<Statement&>(*statement);
            ans->children.push_back(analyseStatement(s));//add all Statement to the children list;
            if(s.ifreturn)  Return_Exist = true;
        }
    }
    if(!Return_Exist)lex.printSemanticError(lex.last,"This Function needs a Return Statement");
    return ans;
}
unique_ptr<SemanticStatement> AST::analyseStatement(Statement& statement) {
    if(statement.ifreturn){
        return make_unique<ReturnStatement>(analyseExpression(*statement.addexp));
    }else{
        return make_unique<AssignmentStatement>(analyseExpression(*statement.assexp));
    }
}
unique_ptr<Expression> AST::analyseExpression(NonTerminal& exp) {
    switch (exp.getType()) {
        case NonTerminal::Add_Exp: {
            auto& add = static_cast<Add_Exp&>(exp);
            if (!add.ifadd) {
                return analyseExpression(*add.multiexp);
            } else {
                if (static_cast<Keyword&>(*add.opr).getType() == Keyword::Type::PLUS) { // "+"
                    return make_unique<BinaryExpression>(add.opr->pos,lex,analyseExpression(*add.multiexp), Keyword::Type::PLUS, analyseExpression(*add.addexp));
                } else {
                    return make_unique<BinaryExpression>(add.opr->pos,lex,analyseExpression(*add.multiexp), Keyword::Type::MINUS, analyseExpression(*add.addexp));
                }
            }
        }
        case NonTerminal::Assign_Exp: {
            auto& assexp = static_cast<Assign_Exp&>(exp);
            string_view name = static_cast<Identifer&>(*assexp.identifer).getName();
            unique_ptr<Expression> addexp = analyseExpression(*assexp.addexp);//see if there is uninitialized symbol
            if (symbolTable.find(name) == symbolTable.end()) {
                lex.printSemanticError(assexp.identifer->pos, name, " is not defined");
            }else if (symbolTable.find(name)->second.getType() == Symbol::Const) {
                lex.printSemanticError(assexp.identifer->pos, name, " is Const, Assignment to a Const variable is not allowed");
            }else if (symbolTable.find(name)->second.getType() == Symbol::Var) {
                symbolTable[name].ifinit =true;
            }
            return make_unique<AssignExpression>(move(addexp), name);
            break;
        }
        case NonTerminal::Multi_Exp: {
            auto& multi = static_cast<Multi_Exp&>(exp);
            if (!multi.ifop) {
                return analyseExpression(*multi.unexp);
            } else {
                if (static_cast<Keyword&>(*multi.opr).getType() == Keyword::Type::MULTIPLY) { // "*"
                    return make_unique<BinaryExpression>(multi.opr->pos,lex,analyseExpression(*multi.unexp), Keyword::Type::MULTIPLY, analyseExpression(*multi.multiexp));
                } else {
                    return make_unique<BinaryExpression>(multi.opr->pos,lex,analyseExpression(*multi.unexp), Keyword::Type::DIVIDE, analyseExpression(*multi.multiexp));
                }
            }
        }
        case NonTerminal::Prim_Exp: {
            auto& prim = static_cast<Prim_Exp&>(exp);
            if (prim.ifadd) {
                return analyseExpression(*prim.addexp);
            } else {
                if (prim.symbol->getTokenType() == LexToken::Number) {
                    return make_unique<PrimExpression>(static_cast<Number&>(*prim.symbol).getNum());
                } else {
                    string_view name = static_cast<Identifer&>(*prim.symbol).getName();
                    if (symbolTable.find(name) == symbolTable.end()) {
                        lex.printSemanticError(prim.symbol->pos, name, " is not defined");
                    } else if (!symbolTable.find(name)->second.ifinit) {
                        lex.printSemanticError(prim.symbol->pos, name, " is not initialized");
                    }
                    return make_unique<PrimExpression>(name);
                }
            }
        }
        case NonTerminal::Unary_Exp: {
            auto& unary = static_cast<Unary_Exp&>(exp);
            if (unary.ifsign) {
                if (static_cast<Keyword&>(*unary.vorzeichen).getType() == Keyword::Type::MINUS) { // "-"
                    return make_unique<UnaryExpression>(analyseExpression(*unary.primexp), false);
                }
            } // plus do nothing
            return make_unique<UnaryExpression>(analyseExpression(*unary.primexp), true);
        }
        default:
            exit(1);
    }
}
int64_t AST::evaluate(unordered_map<string_view,Symbol>& symbolTable){
    return root->evaluate(symbolTable);
}
Function& AST::getRoot() const {
    return *root;
}
AST::AST(SyntaxParser& sp):lex(sp.lex),root(analyseFuntion(*sp.parse())),isOptimized(false) {
}
} // namespace pljit