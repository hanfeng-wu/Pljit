//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_LEXER_HPP
#define PLJIT_LEXER_HPP
#include "Keyword.hpp"
#include "LexToken.hpp"
#include <list>
#include <memory>
#include <pljit/syntax/expression/Error.hpp>
#include <string>
#include <vector>
using namespace std;
namespace pljit {
class Error;
class Lexer {
    std::string code;
    std::string_view code_view;
    std::unique_ptr<LexToken> define(Position,std::string_view);
    bool validName(std::string_view)const;
    bool validNumber(std::string_view)const;
    public:
    int i;
    int j;
    int lnum;
    Position last;//refers to the last
    std::vector<std::string_view> codelines;
    explicit Lexer(std::string);
    //std::list<std::unique_ptr<LexToken>> tokens;
    bool hasNext()const;
    std::unique_ptr<LexToken> next();
    //void printerror(const Position&, const string&)const;
    void printSyntaxError(const Position&, const string&)const;
    void printSemanticError(const Position&, string_view,const string&)const;
    void printSemanticError(const Position&, const string&)const;
    void printSyntaxError(pljit::Error&)const;
    void printArithmeticError(const Position&, const string&)const;
    //void printerror(pljit::Error&)const;

};
}//namespace pljit

#endif //PLJIT_LEXER_HPP
