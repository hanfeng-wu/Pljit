//
// Created by wuha on 22.07.20.
//
#pragma once
#ifndef PLJIT_ASTVISITOR_HPP
#define PLJIT_ASTVISITOR_HPP
namespace pljit{
class AssignExpression;
class UnaryExpression;
class PrimExpression;
class BinaryExpression;
class ReturnStatement;
class AssignmentStatement;
class Function;
    class ASTVisitor {
        public:
        virtual void visit(const AssignExpression&) = 0;
        virtual void visit(const UnaryExpression&) = 0;
        virtual void visit(const PrimExpression&) = 0;
        virtual void visit(const BinaryExpression&) = 0;
        virtual void visit(const ReturnStatement&) = 0;
        virtual void visit(const AssignmentStatement&) = 0;
        virtual void visit(const Function&) = 0;
    };
}// namespace pljit

#endif //PLJIT_ASTVISITOR_HPP
