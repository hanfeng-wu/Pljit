//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_ADD_EXP_HPP
#define PLJIT_ADD_EXP_HPP

#include "Assign_Exp.hpp"
#include "Multi_Exp.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Add_Exp : public NonTerminal {
    public:
    unique_ptr<NonTerminal> multiexp;
    bool ifadd;
    unique_ptr<LexToken> opr; //+ or -
    unique_ptr<NonTerminal> addexp;
    static unique_ptr<NonTerminal> parse(Lexer&);
    explicit Add_Exp(unique_ptr<NonTerminal>);
    Add_Exp(unique_ptr<NonTerminal>, unique_ptr<LexToken>, unique_ptr<NonTerminal>);
    NonTerminalType getType() const override;
    ~Add_Exp() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_ADD_EXP_HPP
