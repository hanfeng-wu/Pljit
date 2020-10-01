//
// Created by wuha on 21.07.20.
//
#pragma once
#ifndef PLJIT_AST_HPP
#define PLJIT_AST_HPP
#include "Symbol.hpp"
#include "TreeNode/Expression.hpp"
#include "pljit/syntax/SyntaxParser.hpp"
#include <memory>
#include <pljit/lex/Lexer.hpp>
#include <pljit/semantic/TreeNode/Expression.hpp>
#include <pljit/semantic/TreeNode/Function.hpp>
#include <unordered_map>
#include <mutex>
using namespace std;
namespace pljit{
    class AST {
        friend class DeadCodeOptimizer;
        friend class ConstPropOptimizer;
        friend class Evaluator;
        friend class ConstPropOptimizer;
        friend class BinaryExpression;
        friend class PrimExpression;
        friend class AssignExpression;
        friend class Pljit;
        Lexer& lex;
        mutex optimizelock;
        unordered_map<string_view,Symbol> symbolTable;//see if a variable is initalized
        list<string_view> parameterlist;
        unique_ptr<Function> root;
        unique_ptr<Function> analyseFuntion(Function_Def& fd);
        unique_ptr<SemanticStatement> analyseStatement(Statement& statement);
        unique_ptr<Expression> analyseExpression(NonTerminal& exp);
        int64_t evaluate(unordered_map<string_view,Symbol>&);//evaluate the return value of the function it represents
        bool isOptimized;
        public:
        explicit AST(SyntaxParser& sp);
        ~AST() = default;
        Function& getRoot() const;

    };

    }// namespace pljit

#endif //PLJIT_AST_HPP
