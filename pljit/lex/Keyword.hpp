//
// Created by wuha on 08.07.20.
//
#pragma once
#ifndef PLJIT_KEYWORD_HPP
#define PLJIT_KEYWORD_HPP

#include "LexToken.hpp"
namespace pljit {
class Keyword : public LexToken {
    public:
    enum class Type {
        PARAM, //"PARAM"
        RETURN,//"RETURN"
        VAR, //"VAR"
        CONST, //"CONST"
        PLUS, //+
        MINUS, //-
        MULTIPLY, //*
        DIVIDE, // /
        LeftPrent, //(
        RightPrent, //)
        ConstAssign,// =
        Assign, //:=
        BEGIN,
        END

    };
    Type getType()const;
    Keyword(Position,TokenType, Type);
    ~Keyword() override = default;
    TokenType getTokenType() override;
    void accept(TreeVisitor&) const override;
    private:
    Type type;
};
}//namespace pljit
#endif //PLJIT_KEYWORD_HPP
