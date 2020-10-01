//
// Created by wuha on 05.07.20.
//

#include "Function.hpp"
namespace pljit{
    void pljit::Function::accept(pljit::ASTVisitor& ast) const {
        ast.visit(*this);
    }
    int64_t Function::evaluate(unordered_map<string_view,Symbol>& symbolTable) const {
        for(auto& statement : children){
            if(statement->ifreturn()){
                return statement->evaluate(symbolTable);
            }else statement->evaluate(symbolTable);
        }
        return 0;
    }
    }//namespace pljit
