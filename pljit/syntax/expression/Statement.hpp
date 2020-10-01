//
// Created by wuha on 12.07.20.
//
#pragma once
#ifndef PLJIT_STATEMENT_HPP
#define PLJIT_STATEMENT_HPP

#include "Add_Exp.hpp"
#include "Assign_Exp.hpp"
#include "Const_Dec.hpp"
#include "Dec_List.hpp"
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
class Statement : public NonTerminal {
    public:
    unique_ptr<NonTerminal> assexp;
    bool ifreturn;
    unique_ptr<LexToken> returnToken;
    unique_ptr<NonTerminal> addexp;
    static unique_ptr<NonTerminal> parse(Lexer&);
    NonTerminalType getType() const override;
    ~Statement() override = default;
    explicit Statement(unique_ptr<NonTerminal>);
    Statement(unique_ptr<LexToken>, unique_ptr<NonTerminal>);
    void accept(TreeVisitor&) const override;
};

} // namespace pljit
#endif //PLJIT_STATEMENT_HPP
