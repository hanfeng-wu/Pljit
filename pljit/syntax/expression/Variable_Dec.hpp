//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_VARIABLE_DEC_HPP
#define PLJIT_VARIABLE_DEC_HPP

#include "Dec_List.hpp"
#include "Init_Dec.hpp"
#include "Init_List.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Variable_Dec : public NonTerminal {
    public:
    unique_ptr<LexToken> var; //"VAR"
    unique_ptr<NonTerminal> declist;
    unique_ptr<LexToken> semi; //";
    static unique_ptr<NonTerminal> parse(Lexer&); // "
    NonTerminalType getType() const override;
    Variable_Dec(unique_ptr<LexToken>, unique_ptr<NonTerminal>, unique_ptr<LexToken>);
    ~Variable_Dec() override = default;
    void accept(TreeVisitor&) const override;
};
} // namespace pljit

#endif //PLJIT_VARIABLE_DEC_HPP
