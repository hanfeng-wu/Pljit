//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_MULTI_EXP_HPP
#define PLJIT_MULTI_EXP_HPP
#include "Add_Exp.hpp"
#include "Assign_Exp.hpp"
#include "Unary_Exp.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Multi_Exp : public NonTerminal {
    public:
    unique_ptr<NonTerminal> unexp;
    bool ifop;
    unique_ptr<LexToken> opr; //* or /
    unique_ptr<NonTerminal> multiexp;
    static unique_ptr<NonTerminal> parse(Lexer&);
    explicit Multi_Exp(unique_ptr<NonTerminal>);
    Multi_Exp(unique_ptr<NonTerminal>, unique_ptr<LexToken>, unique_ptr<NonTerminal>);
    NonTerminalType getType() const override;
    ~Multi_Exp() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_MULTI_EXP_HPP
