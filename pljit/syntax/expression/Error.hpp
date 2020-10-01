//
// Created by wuha on 12.07.20.
//
#pragma once
#ifndef PLJIT_ERROR_HPP
#define PLJIT_ERROR_HPP
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {

class Error : public NonTerminal {
    public:
    Position pos;
    string message;
    Error(Position, string);
    NonTerminalType getType() const override;
    ~Error() override = default;
    void accept(TreeVisitor&) const override;
};
} // namespace pljit

#endif //PLJIT_ERROR_HPP
