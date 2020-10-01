//
// Created by wuha on 09.07.20.
//
#pragma once
#ifndef PLJIT_NUMBER_HPP
#define PLJIT_NUMBER_HPP
#include "LexToken.hpp"
#include <string>
namespace pljit {
class Number : public LexToken {
    int64_t num;

    public:
    Number(Position, TokenType, std::string_view);
    ~Number() override = default;
    TokenType getTokenType() override;
    int64_t getNum() const;
    void accept(TreeVisitor&) const override;
};
} // namespace pljit

#endif //PLJIT_NUMBER_HPP
