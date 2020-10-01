//
// Created by wuha on 12.07.20.
//
#pragma once
#ifndef PLJIT_NONTERMINAL_HPP
#define PLJIT_NONTERMINAL_HPP
#include "SyntaxNode.hpp"
#include <memory>
using namespace std;
namespace pljit {
class NonTerminal : public SyntaxNode {
    public:
    enum NonTerminalType {
        Add_Exp,
        Assign_Exp,
        Multi_Exp,
        Prim_Exp,
        Unary_Exp,
        Comp_Statement,
        Const_Dec,
        Dec_List,
        Error,
        Funtion_Def,
        Init_Dec,
        Init_List,
        Parameter_Dec,
        Statement,
        Statement_List,
        Variable_Dec
    };
    virtual NonTerminalType getType() const = 0;
    ~NonTerminal()override = default;
    bool isTerminal() override;
};

} // namespace pljit

#endif //PLJIT_NONTERMINAL_HPP
