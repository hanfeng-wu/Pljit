//
// Created by wuha on 01.08.20.
//
#pragma once
#ifndef PLJIT_EVALUATOR_HPP
#define PLJIT_EVALUATOR_HPP
#include "AST.hpp"
namespace pljit{
    class Evaluator {
        friend class Pljit;
        AST& ast;//in the ast stores all the variables
        unordered_map<string_view,Symbol> symbolTable;
        public:
        explicit Evaluator(AST& ast);
        ~Evaluator() =default;
        int64_t evaluate();
    };
}// namespace pljit

#endif //PLJIT_EVALUATOR_HPP
