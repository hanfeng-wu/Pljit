//
// Created by wuha on 22.07.20.
//
#pragma once
#ifndef PLJIT_ASTPRINTDOTVISITOR_HPP
#define PLJIT_ASTPRINTDOTVISITOR_HPP
#include "ASTVisitor.hpp"
namespace pljit{
    class ASTPrintDotVisitor : public ASTVisitor{
        int number;
        public:
        void visit(const AssignExpression& expression) override;
        void visit(const UnaryExpression& expression) override;
        void visit(const PrimExpression& expression) override;
        void visit(const BinaryExpression& expression) override;
        void visit(const ReturnStatement& statement) override;
        void visit(const AssignmentStatement& statement) override;
        void visit(const Function& function) override;
        ASTPrintDotVisitor();
    };
}// namespace pljit

#endif //PLJIT_ASTPRINTDOTVISITOR_HPP
