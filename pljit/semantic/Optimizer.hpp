//
// Created by wuha on 01.08.20.
//
#pragma once
#ifndef PLJIT_OPTIMIZER_HPP
#define PLJIT_OPTIMIZER_HPP
#include "AST.hpp"
namespace pljit{
    class Optimizer {
        public:
        virtual void optimize(AST& ast) const = 0;
    };
    class DeadCodeOptimizer : public Optimizer{
        public:
        void optimize(AST& ast) const override;
    };
    class ConstPropOptimizer : public Optimizer{
        public:
        void optimize(AST& ast) const override;
    };
}// namespace pljit

#endif //PLJIT_OPTIMIZER_HPP
