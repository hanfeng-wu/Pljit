//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_IDENTIFER_HPP
#define PLJIT_IDENTIFER_HPP

#include "LexToken.hpp"
#include <string>
namespace pljit {
class Identifer : public LexToken {
    std::string_view name;

    public:
    Identifer(Position,TokenType, std::string_view);
    ~Identifer() override = default;
    TokenType getTokenType() override;
    std::string_view getName() const;
    void accept(TreeVisitor&) const override;
};
}//namespace pljit
#endif //PLJIT_IDENTIFER_HPP
