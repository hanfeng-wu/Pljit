//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_ASSIGN_EXP_HPP
#define PLJIT_ASSIGN_EXP_HPP

#include "Add_Exp.hpp"
#include "Assign_Exp.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Assign_Exp : public NonTerminal {
    public:
    unique_ptr<LexToken> identifer;
    unique_ptr<LexToken> assign;
    unique_ptr<NonTerminal> addexp;
    static unique_ptr<NonTerminal> parse(Lexer&);
    Assign_Exp(unique_ptr<LexToken>, unique_ptr<LexToken>, unique_ptr<NonTerminal>);
    NonTerminalType getType() const override;
    ~Assign_Exp() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_ASSIGN_EXP_HPP
