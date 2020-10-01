//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_PRIM_EXP_HPP
#define PLJIT_PRIM_EXP_HPP

#include "Add_Exp.hpp"
#include "Assign_Exp.hpp"
#include "Prim_Exp.hpp"
#include "Unary_Exp.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>

using namespace std;
namespace pljit {
class Prim_Exp : public NonTerminal {
    public:
    bool ifadd; // if it is addtive expression
    unique_ptr<LexToken> symbol; // identifer ot literal
    unique_ptr<LexToken> leftprent; //(
    unique_ptr<NonTerminal> addexp;
    unique_ptr<LexToken> rightprent; //)
    static unique_ptr<NonTerminal> parse(Lexer&);
    explicit Prim_Exp(unique_ptr<LexToken>); //accept a identifer or a number
    Prim_Exp(unique_ptr<LexToken>, unique_ptr<NonTerminal>, unique_ptr<LexToken>); //(Add_Exp)
    NonTerminalType getType() const override;
    ~Prim_Exp() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_PRIM_EXP_HPP
