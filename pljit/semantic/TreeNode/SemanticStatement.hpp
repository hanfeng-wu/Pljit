//
// Created by wuha on 21.07.20.
//
#pragma once
#ifndef PLJIT_SEMANTICSTATEMENT_HPP
#define PLJIT_SEMANTICSTATEMENT_HPP
#include "Expression.hpp"
#include "SemanticTreeNode.hpp"
#include <memory>
#include <pljit/lex/Identifer.hpp>
using namespace std;
namespace pljit{
    class SemanticStatement : public SemanticTreeNode {
        public:
        virtual bool ifreturn()const = 0;
        virtual int64_t evaluate(unordered_map<string_view,Symbol>&)const = 0;
        virtual void optimize(AST&,unordered_map<string_view,Symbol>& optimizetable) = 0;
    };
    class ReturnStatement : public SemanticStatement {
        public:
        unique_ptr<Expression> exp;
        explicit ReturnStatement(unique_ptr<Expression>);
        void accept(ASTVisitor&) const override;
        ~ReturnStatement() override = default;
        bool ifreturn()const override;
        int64_t evaluate(unordered_map<string_view,Symbol>&) const override;
        void optimize(AST&,unordered_map<string_view,Symbol>& optimizetable) override;
    };
    class AssignmentStatement : public SemanticStatement {
        public:
        unique_ptr<Expression> exp;
        explicit AssignmentStatement(unique_ptr<Expression>);
        void accept(ASTVisitor&) const override;
        ~AssignmentStatement() override = default;
        bool ifreturn()const override;
        int64_t evaluate(unordered_map<string_view,Symbol>&) const override ;
        void optimize(AST&,unordered_map<string_view,Symbol>& optimizetable) override;

    };
}// namespace pljit

#endif //PLJIT_SEMANTICSTATEMENT_HPP
