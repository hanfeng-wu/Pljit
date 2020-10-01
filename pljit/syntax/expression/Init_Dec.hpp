//
// Created by wuha on 12.07.20.
//
#pragma once
#ifndef PLJIT_INIT_DEC_HPP
#define PLJIT_INIT_DEC_HPP

#include "Const_Dec.hpp"
#include "Dec_List.hpp"
#include "Init_Dec.hpp"
#include "Init_List.hpp"
#include "Parameter_Dec.hpp"
#include "Variable_Dec.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Init_Dec : public NonTerminal {
    public:
    unique_ptr<LexToken> identifer;
    unique_ptr<LexToken> ConstAssign; //"="
    unique_ptr<LexToken> literal; //number
    static unique_ptr<NonTerminal> parse(pljit::Lexer&);
    NonTerminalType getType() const override;
    Init_Dec(unique_ptr<LexToken>, unique_ptr<LexToken>, unique_ptr<LexToken>);
    ~Init_Dec() override = default;
    void accept(TreeVisitor&) const override;
};
} // namespace pljit

#endif //PLJIT_INIT_DEC_HPP
