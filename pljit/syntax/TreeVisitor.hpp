//
// Created by wuha on 16.07.20.
//
#pragma once
#ifndef PLJIT_TREEVISITOR_HPP
#define PLJIT_TREEVISITOR_HPP
namespace pljit {
class Identifer;
class Keyword;
class Number;
class Separator;
class Add_Exp;
class Assign_Exp;
class Multi_Exp;
class Prim_Exp;
class Unary_Exp;
class Comp_Statement;
class Const_Dec;
class Dec_List;
class Function_Def;
class Init_Dec;
class Init_List;
class Parameter_Dec;
class Statement;
class Statement_List;
class Variable_Dec;

class TreeVisitor {
    public:
    virtual void visit(const Identifer&) = 0;
    virtual void visit(const Keyword&) = 0;
    virtual void visit(const Number&) = 0;
    virtual void visit(const Separator&) = 0;
    virtual void visit(const Add_Exp&) = 0;
    virtual void visit(const Assign_Exp&) = 0;
    virtual void visit(const Multi_Exp&) = 0;
    virtual void visit(const Prim_Exp&) = 0;
    virtual void visit(const Unary_Exp&) = 0;
    virtual void visit(const Comp_Statement&) = 0;
    virtual void visit(const Const_Dec&) = 0;
    virtual void visit(const Dec_List&) = 0;
    virtual void visit(const Function_Def&) = 0;
    virtual void visit(const Init_Dec&) = 0;
    virtual void visit(const Init_List&) = 0;
    virtual void visit(const Parameter_Dec&) = 0;
    virtual void visit(const Statement&) = 0;
    virtual void visit(const Statement_List&) = 0;
    virtual void visit(const Variable_Dec&) = 0;
};
} // namespace pljit
#endif //PLJIT_TREEVISITOR_HPP
