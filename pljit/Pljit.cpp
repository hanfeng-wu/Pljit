//
// Created by wuha on 06.08.20.
//

#include "Pljit.hpp"
#include <iostream>
using namespace std;
namespace pljit{
    int64_t pljit::Pljit::Funktion::operator()(vector<int64_t> paras)const  {
        if(!ast->isOptimized){
            ast->optimizelock.lock();//allow only one thread to optimize the ast
            if(ast->isOptimized){
                ast->optimizelock.unlock();
                goto a;//skip the optimization, if another thread has already optimized it
            }
            DeadCodeOptimizer deadCodeOptimizer;
            deadCodeOptimizer.optimize(*ast);
            ConstPropOptimizer constPropOptimizer;
            constPropOptimizer.optimize(*ast);
            ast->isOptimized = true;
            ast->optimizelock.unlock();
        }
        a:Evaluator evaluator(*ast);
        int i=0;
        if(paras.size()!=ast->parameterlist.size()){
            cerr<<"Error: Number of Parameters doesn't match. should be: "<<ast->parameterlist.size()<<" while actual is: "<<paras.size()<<endl;
            exit(1);
        }
        for(auto& name : ast->parameterlist){
            evaluator.symbolTable[name].setValue(paras[i++]);//set the parameter
        }
        return evaluator.evaluate();
    }
    Pljit::Funktion::Funktion(AST* ast):ast(ast),ifoptimized(false) {

    }
    Pljit::Funktion Pljit::registerFunction(const string& s) {
        unique_lock l{lock};
        lexer.emplace_back(s);
        syntaxParser.emplace_back(lexer.back());
        ast.emplace_back(syntaxParser.back());
        return (Funktion(&ast.back()));
    }
    }// namespace pljit