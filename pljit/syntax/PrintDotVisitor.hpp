//
// Created by wuha on 16.07.20.
//
#pragma once
#ifndef PLJIT_PRINTDOTVISITOR_HPP
#define PLJIT_PRINTDOTVISITOR_HPP
#include "TreeVisitor.hpp"
namespace pljit {

class PrintDotVisitor : public TreeVisitor {
    int number;
    public:
    void visit(const Identifer& identifer) override;
    void visit(const Keyword& keyword) override;
    void visit(const Number& number) override;
    void visit(const Separator& separator) override;
    void visit(const Add_Exp& exp) override;
    void visit(const Assign_Exp& exp) override;
    void visit(const Multi_Exp& exp) override;
    void visit(const Prim_Exp& exp) override;
    void visit(const Unary_Exp& exp) override;
    void visit(const Comp_Statement& statement) override;
    void visit(const Const_Dec& dec) override;
    void visit(const Dec_List& list) override;
    void visit(const Function_Def& def) override;
    void visit(const Init_Dec& dec) override;
    void visit(const Init_List& list) override;
    void visit(const Parameter_Dec& dec) override;
    void visit(const Statement& statement) override;
    void visit(const Statement_List& list) override;
    void visit(const Variable_Dec& dec) override;
    PrintDotVisitor();
};
} // namespace pljit

#endif //PLJIT_PRINTDOTVISITOR_HPP
