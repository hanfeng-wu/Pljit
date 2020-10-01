//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_DEC_LIST_HPP
#define PLJIT_DEC_LIST_HPP
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {

class Dec_List : public NonTerminal {
    public:
    list<unique_ptr<LexToken>> children;
    static unique_ptr<NonTerminal> parse(Lexer&);
    NonTerminalType getType() const override;
    Dec_List() = default;
    ~Dec_List() override = default;
    void accept(TreeVisitor&) const override;
};
} // namespace pljit

#endif //PLJIT_DEC_LIST_HPP
