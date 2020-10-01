//
// Created by wuha on 01.08.20.
//

#include "Evaluator.hpp"
namespace pljit{
    pljit::Evaluator::Evaluator(AST & ast):ast(ast),symbolTable(unordered_map<string_view,Symbol>{ast.symbolTable}) {//copy a symbol table to evaluate
    }
    int64_t Evaluator::evaluate()  {
        return ast.evaluate(symbolTable);
    }
}//namespace pljit