//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_INIT_LIST_HPP
#define PLJIT_INIT_LIST_HPP

#include "Init_Dec.hpp"
#include "Init_List.hpp"
#include "pljit/lex/LexToken.hpp"
#include "pljit/lex/Lexer.hpp"
#include <memory>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Init_List : public NonTerminal {
    public:
    list<unique_ptr<SyntaxNode>> children;
    static unique_ptr<NonTerminal> parse(Lexer&);
    Init_List() = default;
    NonTerminalType getType() const override;
    ~Init_List() override = default;
    void accept(TreeVisitor&) const override;
};
} // namespace pljit

#endif //PLJIT_INIT_LIST_HPP
