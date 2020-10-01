//
// Created by wuha on 21.07.20.
//
#pragma once
#ifndef PLJIT_SYNTAXPARSER_HPP
#define PLJIT_SYNTAXPARSER_HPP
#include "expression/Function_Def.hpp"
namespace pljit{
    class SyntaxParser {
        friend class AST;
        Lexer& lex;
        public:
        unique_ptr<Function_Def> parse();
        explicit SyntaxParser(Lexer&);
    };
}// namespace pljit

#endif //PLJIT_SYNTAXPARSER_HPP
