//
// Created by wuha on 21.07.20.
//

#include "SemanticStatement.hpp"
namespace pljit{
    ReturnStatement::ReturnStatement(unique_ptr<Expression> exp):exp(move(exp)) {
    }
    void ReturnStatement::accept(ASTVisitor& ast) const {
        ast.visit(*this);
    }
    bool ReturnStatement::ifreturn() const {
        return true;
    }
    int64_t ReturnStatement::evaluate(unordered_map<string_view,Symbol>& symbolTable) const {
        return exp->evaluate(symbolTable);
    }
    void ReturnStatement::optimize(AST& ast,unordered_map<string_view,Symbol>& optimizetable) {
        exp->optimize(ast,exp,optimizetable);
    }
    AssignmentStatement::AssignmentStatement(unique_ptr<Expression> exp):exp(move(exp)) {
    }
    void AssignmentStatement::accept(ASTVisitor& ast) const {
        ast.visit(*this);
    }
    bool AssignmentStatement::ifreturn() const {
        return false;
    }
    int64_t AssignmentStatement::evaluate(unordered_map<string_view,Symbol>& symbolTable) const {
        return exp->evaluate(symbolTable);
    }
    void AssignmentStatement::optimize(AST& ast,unordered_map<string_view,Symbol>& optimizetable) {
        exp->optimize(ast,exp,optimizetable);
    }
    }// namespace pljit
