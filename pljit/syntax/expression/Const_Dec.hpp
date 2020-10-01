//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_CONST_DEC_HPP
#define PLJIT_CONST_DEC_HPP

#include "Init_List.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Const_Dec : public NonTerminal {
    public:
    unique_ptr<LexToken> constsym; //"CONST"
    unique_ptr<NonTerminal> initlist;
    unique_ptr<LexToken> semi; //";"
    static unique_ptr<NonTerminal> parse(Lexer&);
    NonTerminalType getType() const override;
    Const_Dec(unique_ptr<LexToken>, unique_ptr<NonTerminal>, unique_ptr<LexToken>);
    ~Const_Dec() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit
#endif //PLJIT_CONST_DEC_HPP
