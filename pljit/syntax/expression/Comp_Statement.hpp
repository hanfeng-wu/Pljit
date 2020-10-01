//
// Created by wuha on 12.07.20.
//
#pragma once
#ifndef PLJIT_COMP_STATEMENT_HPP
#define PLJIT_COMP_STATEMENT_HPP
#include "Const_Dec.hpp"
#include "Dec_List.hpp"
#include "Parameter_Dec.hpp"
#include "Statement_List.hpp"
#include "Variable_Dec.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Comp_Statement : public NonTerminal {
    public:
    unique_ptr<LexToken> begin;
    unique_ptr<NonTerminal> statelist;
    unique_ptr<LexToken> end;
    Comp_Statement(unique_ptr<LexToken>, unique_ptr<NonTerminal>, unique_ptr<LexToken>);
    static unique_ptr<NonTerminal> parse(Lexer&);
    NonTerminalType getType() const override;
    ~Comp_Statement() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_COMP_STATEMENT_HPP
