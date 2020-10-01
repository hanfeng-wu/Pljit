//
// Created by wuha on 21.07.20.
//
#pragma once
#ifndef PLJIT_EXPRESSION_HPP
#define PLJIT_EXPRESSION_HPP
#include "SemanticTreeNode.hpp"
#include "pljit/semantic/ASTVisitor.hpp"
#include <memory>
#include <pljit/lex/Identifer.hpp>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/semantic/Symbol.hpp>
#include <unordered_map>
using namespace std;
namespace pljit{
class AST;
class ASTVisitor;
    class Expression :public SemanticTreeNode{
        public:
        virtual int64_t evaluate(unordered_map<string_view,Symbol>&) const =0;
        virtual bool optimize(AST&,unique_ptr<Expression>& thisRef,unordered_map<string_view,Symbol>& optimizetable) = 0;

    };
    class AssignExpression: public Expression{
        public:
        unique_ptr<Expression> exp;
        string_view name;
        AssignExpression(unique_ptr<Expression>,string_view);
        void accept(ASTVisitor&) const override;
        ~AssignExpression() override = default;
        int64_t evaluate(unordered_map<string_view,Symbol>&) const override;
        bool optimize(AST&,unique_ptr<Expression>& thisRef,unordered_map<string_view,Symbol>& optimizetable) override;

    };
    class UnaryExpression: public Expression{
        public:
        unique_ptr<Expression> exp;
        bool sign;//true when it is + false when -
        UnaryExpression(unique_ptr<Expression>,bool);
        void accept(ASTVisitor&) const override;
        ~UnaryExpression() override = default;
        int64_t evaluate(unordered_map<string_view,Symbol>&) const override;
        bool optimize(AST&,unique_ptr<Expression>& thisRef,unordered_map<string_view,Symbol>& optimizetable) override;

    };
    class PrimExpression: public Expression{
        public:
        enum PrimType{
            Id,
            Num,
            Addexp
        };
        string_view name;
        int64_t number;
        unique_ptr<Expression> addexp;
        PrimType getType() const;
        explicit PrimExpression(string_view);
        explicit PrimExpression(int64_t);
        explicit PrimExpression(unique_ptr<Expression>);
        void accept(ASTVisitor&) const override;
        ~PrimExpression() override = default;
        int64_t evaluate(unordered_map<string_view,Symbol>&) const override;
        bool optimize(AST&,unique_ptr<Expression>& thisRef,unordered_map<string_view,Symbol>& optimizetable) override;

        private:
        PrimType type;

};
    class BinaryExpression: public Expression{
        Position pos;
        Lexer& lex;
        public:
        BinaryExpression(Position,Lexer&,unique_ptr<Expression>,Keyword::Type,unique_ptr<Expression>);
        unique_ptr<Expression> left;
        Keyword::Type opr;//+ - * /
        unique_ptr<Expression> right;
        void accept(ASTVisitor&) const override;
        ~BinaryExpression() override = default;
        int64_t evaluate(unordered_map<string_view,Symbol>&) const override;
        bool optimize(AST&,unique_ptr<Expression>& thisRef,unordered_map<string_view,Symbol>& optimizetable) override;

    };
}// namespace pljit

#endif //PLJIT_EXPRESSION_HPP
