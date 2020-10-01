//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_SEPARATOR_HPP
#define PLJIT_SEPARATOR_HPP

#include "LexToken.hpp"
namespace pljit {
class Separator : public LexToken{
    public:
    enum SepType{
        COMMA,//,
        SEMI,//;
        POINT//.
    };
    SepType getType() const;
    Separator(Position,TokenType, SepType);
    ~Separator() override = default;
    TokenType getTokenType() override;
    void accept(TreeVisitor&) const override;
    private:
    SepType type;
};
}//namespace pljit

#endif //PLJIT_SEPARATOR_HPP
