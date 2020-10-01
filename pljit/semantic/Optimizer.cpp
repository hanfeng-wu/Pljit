//
// Created by wuha on 01.08.20.
//

#include "Optimizer.hpp"
namespace pljit{

void DeadCodeOptimizer::optimize(AST& ast) const {
    if(ast.isOptimized)return;
    Function& root = ast.getRoot();
    for(auto a = root.children.begin();a!=root.children.end();a++){
        if(a->get()->ifreturn()){
            root.children.erase(++a,root.children.end());//remove all elements after return statement
            break;
        }
    }
}
void ConstPropOptimizer::optimize(AST& ast) const {
    if(ast.isOptimized)return;
    unordered_map<string_view,Symbol> optimizeTable {ast.symbolTable};
    Function& root = ast.getRoot();
    for(auto& a : root.children){
        a->optimize(ast,optimizeTable);
    }

}
}// namespace pljit