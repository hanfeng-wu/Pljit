//
// Created by wuha on 12.07.20.
//
#pragma once
#ifndef PLJIT_STATEMENT_LIST_HPP
#define PLJIT_STATEMENT_LIST_HPP

#include "Const_Dec.hpp"
#include "Dec_List.hpp"
#include "Parameter_Dec.hpp"
#include "Statement.hpp"
#include "Variable_Dec.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
using namespace std;
namespace pljit {
class Statement_List : public NonTerminal {
    public:
    list<unique_ptr<SyntaxNode>> children; //check if ; exists in between
    static unique_ptr<NonTerminal> parse(Lexer&);
    Statement_List() = default;
    NonTerminalType getType() const override;
    ~Statement_List() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_STATEMENT_LIST_HPP
