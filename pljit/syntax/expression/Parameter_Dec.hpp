//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_PARAMETER_DEC_HPP
#define PLJIT_PARAMETER_DEC_HPP
#include "Dec_List.hpp"
#include "pljit/lex/LexToken.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <vector>
using namespace std;
namespace pljit {
class Parameter_Dec : public NonTerminal {
    public:
    unique_ptr<LexToken> param;
    unique_ptr<NonTerminal> declist;
    unique_ptr<LexToken> semi;
    static unique_ptr<NonTerminal> parse(Lexer&);
    NonTerminalType getType() const override;
    Parameter_Dec(unique_ptr<LexToken>, unique_ptr<NonTerminal>, unique_ptr<LexToken>);
    ~Parameter_Dec() override = default;
    void accept(TreeVisitor&) const override;
};
} // namespace pljit
#endif //PLJIT_PARAMETER_DEC_HPP
