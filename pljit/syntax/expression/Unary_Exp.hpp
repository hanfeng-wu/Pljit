//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_UNARY_EXP_HPP
#define PLJIT_UNARY_EXP_HPP

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
class Unary_Exp : public NonTerminal {
    public:
    bool ifsign;
    unique_ptr<LexToken> vorzeichen; //- or +
    unique_ptr<NonTerminal> primexp;
    static unique_ptr<NonTerminal> parse(Lexer&);
    Unary_Exp(unique_ptr<LexToken>, unique_ptr<NonTerminal>);
    explicit Unary_Exp(unique_ptr<NonTerminal>);
    NonTerminalType getType() const override;
    ~Unary_Exp() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_UNARY_EXP_HPP
