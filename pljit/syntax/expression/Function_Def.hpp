//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_FUNCTION_DEF_HPP
#define PLJIT_FUNCTION_DEF_HPP
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
class Function_Def : public NonTerminal {
    public:
    bool ifpara; //true when there's a parameter declaration
    unique_ptr<NonTerminal> paradec;
    bool ifvar; //true when there's a variable declaration
    unique_ptr<NonTerminal> varadec;
    bool ifcon; //true when there's a const declaration
    unique_ptr<NonTerminal> constdec;
    unique_ptr<NonTerminal> comp_states;
    unique_ptr<LexToken> point;
    static unique_ptr<Function_Def> parse(Lexer&);
    NonTerminalType getType() const override;
    Function_Def(unique_ptr<NonTerminal>, unique_ptr<LexToken>); //only initiallize the comp_states and point
    ~Function_Def() override = default;
    void accept(TreeVisitor&) const override;
};

} // namespace pljit

#endif //PLJIT_FUNCTION_DEF_HPP
