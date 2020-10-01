//
// Created by wuha on 06.08.20.
//
#pragma once
#ifndef PLJIT_PLJIT_HPP
#define PLJIT_PLJIT_HPP
#include "lex/Lexer.hpp"
#include <functional>
#include <mutex>
#include <pljit/semantic/AST.hpp>
#include <pljit/semantic/Evaluator.hpp>
#include <pljit/semantic/Optimizer.hpp>
#include <pljit/syntax/SyntaxParser.hpp>
using namespace std;
namespace pljit{
    class Pljit {
            mutex lock;
            list<Lexer> lexer;
            list<SyntaxParser> syntaxParser;
            list<AST> ast;
        struct Funktion{
            private:
            AST* ast;
            bool ifoptimized;
            public:
            int64_t operator ()(vector<int64_t>) const;
            explicit Funktion(AST*);
            Funktion& operator=(const Funktion&) = default;
            Funktion(const Funktion&)= default;
        };
        public:
        Funktion registerFunction(const string&);
    };
}// namespace pljit

#endif //PLJIT_PLJIT_HPP
