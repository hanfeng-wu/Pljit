//
// Created by wuha on 08.07.20.
//
#pragma once
#ifndef PLJIT_LEXTOKEN_HPP
#define PLJIT_LEXTOKEN_HPP
#include <memory>
#include <pljit/lex/Position.hpp>
#include <pljit/syntax/Node/SyntaxNode.hpp>
using namespace std;
namespace pljit {
class LexToken : public SyntaxNode{
    public:
    Position pos;
    enum TokenType{
        Identifer,
        Keyword,
        Separator,
        Number
    };
    explicit LexToken(Position,TokenType);
    ~LexToken() override;
    virtual TokenType getTokenType() =0;
    bool isTerminal() override;
    private:
    TokenType tokenType;
};
}//namespace pljit

#endif //PLJIT_LEXTOKEN_HPP
