//
// Created by wuha on 16.07.20.
//

#include "PrintDotVisitor.hpp"
#include "expression/Add_Exp.hpp"
#include "pljit/lex/Identifer.hpp"
#include "pljit/lex/Keyword.hpp"
#include "pljit/lex/Number.hpp"
#include "pljit/lex/Separator.hpp"
#include "pljit/syntax/expression/Comp_Statement.hpp"
#include "pljit/syntax/expression/Function_Def.hpp"
#include "pljit/syntax/expression/Statement.hpp"
#include <iostream>
using namespace std;
namespace pljit {
void pljit::PrintDotVisitor::visit(const pljit::Identifer& identifer) {
    cout << "\t" << number++ << " [label=\"" << identifer.getName() << "\"];\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Keyword& keyword) {
    switch (keyword.getType()) {
        case Keyword::Type::PARAM: cout << "\t" << number++ << " [label=\"PARAM\"];\n"; break;
        case Keyword::Type::RETURN: cout << "\t" << number++ << " [label=\"RETURN\"];\n"; break;
        case Keyword::Type::VAR: cout << "\t" << number++ << " [label=\"VAR\"];\n"; break;
        case Keyword::Type::CONST: cout << "\t" << number++ << " [label=\"CONST\"];\n"; break;
        case Keyword::Type::PLUS: cout << "\t" << number++ << " [label=\"+\"];\n"; break;
        case Keyword::Type::MINUS: cout << "\t" << number++ << " [label=\"-\"];\n"; break;
        case Keyword::Type::MULTIPLY: cout << "\t" << number++ << " [label=\"*\"];\n"; break;
        case Keyword::Type::DIVIDE: cout << "\t" << number++ << " [label=\"/\"];\n"; break;
        case Keyword::Type::LeftPrent: cout << "\t" << number++ << " [label=\"(\"];\n"; break;
        case Keyword::Type::RightPrent: cout << "\t" << number++ << " [label=\")\"];\n"; break;
        case Keyword::Type::ConstAssign: cout << "\t" << number++ << " [label=\"=\"];\n"; break;
        case Keyword::Type::Assign: cout << "\t" << number++ << " [label=\":=\"];\n"; break;
        case Keyword::Type::BEGIN: cout << "\t" << number++ << " [label=\"BEGIN\"];\n"; break;
        case Keyword::Type::END: cout << "\t" << number++ << " [label=\"END\"];\n"; break;
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Number& number) {
    cout << "\t" << this->number++ << " [label=\"" << number.getNum() << "\"];\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Separator& separator) {
    switch (separator.getType()) {
        case Separator::COMMA: cout << "\t" << number++ << " [label=\",\"];\n"; break;
        case Separator::SEMI: cout << "\t" << number++ << " [label=\";\"];\n"; break;
        case Separator::POINT: cout << "\t" << number++ << " [label=\".\"];\n"; break;
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Add_Exp& exp) {
    int thisnum = number;
    int multinum;
    int oprnum;
    int addnum;
    cout << "\t" << number++ << " [label=\"additive-expression\"];\n";
    multinum = number;
    exp.multiexp->accept(*this);
    cout << "\t" << thisnum << " -> " << multinum << ";\n";
    if (exp.ifadd) {
        oprnum = number;
        exp.opr->accept(*this);
        cout << "\t" << thisnum << " -> " << oprnum << ";\n";
        addnum = number;
        exp.addexp->accept(*this);
        cout << "\t" << thisnum << " -> " << addnum << ";\n";
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Assign_Exp& exp) {
    int thisnum = number++;
    int idnum;
    int assignnum;
    int addnum;
    cout << "\t" << thisnum << " [label=\"assignment-expression\"];\n";
    idnum = number;
    exp.identifer->accept(*this);
    cout << "\t" << thisnum << " -> " << idnum << ";\n";
    assignnum = number;
    exp.assign->accept(*this);
    cout << "\t" << thisnum << " -> " << assignnum << ";\n";
    addnum = number;
    exp.addexp->accept(*this);
    cout << "\t" << thisnum << " -> " << addnum << ";\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Multi_Exp& exp) {
    int thisnum = number;
    int unarynum;
    int oprnum;
    int multinum;
    cout << "\t" << number++ << " [label=\"multiplicative-expression\"];\n";
    unarynum = number;
    exp.unexp->accept(*this);
    cout << "\t" << thisnum << " -> " << unarynum << ";\n";
    if (exp.ifop) {
        oprnum = number;
        exp.opr->accept(*this);
        cout << "\t" << thisnum << " -> " << oprnum << ";\n";
        multinum = number;
        exp.multiexp->accept(*this);
        cout << "\t" << thisnum << " -> " << multinum << ";\n";
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Prim_Exp& exp) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"primary-expression\"];\n";
    if (exp.ifadd) {
        exp.leftprent->accept(*this);
        cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
        int addnum = number;
        exp.addexp->accept(*this);
        cout << "\t" << thisnum << " -> " << addnum << ";\n";
        exp.rightprent->accept(*this);
        cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
    } else {
        int termnum = number;
        exp.symbol->accept(*this);
        cout << "\t" << thisnum << " -> " << termnum << ";\n";
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Unary_Exp& exp) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"unary-expression\"];\n";
    if (exp.ifsign) {
        exp.vorzeichen->accept(*this);
        cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
    }
    int primnum = number;
    exp.primexp->accept(*this);
    cout << "\t" << thisnum << " -> " << primnum << ";\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Comp_Statement& statement) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"compound-statement\"];\n";
    statement.begin->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
    int slnum = number;
    statement.statelist->accept(*this);
    cout << "\t" << thisnum << " -> " << slnum << ";\n";
    statement.end->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Const_Dec& dec) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"constant-declarations\"];\n";
    dec.constsym->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
    int ilnum = number;
    dec.initlist->accept(*this);
    cout << "\t" << thisnum << " -> " << ilnum << ";\n";
    dec.semi->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Dec_List& list) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"declarator-list\"];\n";
    int tmp;
    for (auto& child : list.children) {
        tmp = number;
        child->accept(*this);
        cout << "\t" << thisnum << " -> " << tmp << ";\n";
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Function_Def& def) {
    int paranum;
    int varnum;
    int connum;
    int comp_statenum;
    int pointnum;
    cout << "digraph {\n";
    cout << "\t0 [label=\"function-definition\"];\n";
    if (def.ifpara) {
        paranum = number;
        def.paradec->accept(*this);
        cout << "\t" << 0 << " -> " << paranum << ";\n";
    }
    if (def.ifvar) {
        varnum = number;
        def.varadec->accept(*this);
        cout << "\t" << 0 << " -> " << varnum << ";\n";
    }
    if (def.ifcon) {
        connum = number;
        def.constdec->accept(*this);
        cout << "\t" << 0 << " -> " << connum << ";\n";
    }
    comp_statenum = number;
    def.comp_states->accept(*this);
    cout << "\t" << 0 << " -> " << comp_statenum << ";\n";
    pointnum = number;
    def.point->accept(*this);
    cout << "\t" << 0 << " -> " << pointnum << ";\n";
    cout << "}\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Init_Dec& dec) {
    int thisnum = number++;
    int idnum;
    int assignnum;
    int numnum;
    cout << "\t" << thisnum << " [label=\"init-declarator\"];\n";
    idnum = number;
    dec.identifer->accept(*this);
    cout << "\t" << thisnum << " -> " << idnum << ";\n";
    assignnum = number;
    dec.ConstAssign->accept(*this);
    cout << "\t" << thisnum << " -> " << assignnum << ";\n";
    numnum = number;
    dec.literal->accept(*this);
    cout << "\t" << thisnum << " -> " << numnum << ";\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Init_List& list) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"init-declarator-list\"];\n";
    int tmp;
    for (auto& child : list.children) {
        tmp = number;
        child->accept(*this);
        cout << "\t" << thisnum << " -> " << tmp << ";\n";
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Parameter_Dec& dec) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"parameter-declarations\"];\n";
    dec.param->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
    int dlnum = number;
    dec.declist->accept(*this);
    cout << "\t" << thisnum << " -> " << dlnum << ";\n";
    dec.semi->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
}
void pljit::PrintDotVisitor::visit(const pljit::Statement& statement) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"statement\"];\n";
    if (statement.ifreturn) {
        statement.returnToken->accept(*this);
        cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
        int addnum = number;
        statement.addexp->accept(*this);
        cout << "\t" << thisnum << " -> " << addnum << ";\n";
    } else {
        int assnum = number;
        statement.assexp->accept(*this);
        cout << "\t" << thisnum << " -> " << assnum << ";\n";
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Statement_List& list) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"statement-list\"];\n";
    int tmp;
    for (auto& child : list.children) {
        tmp = number;
        child->accept(*this);
        cout << "\t" << thisnum << " -> " << tmp << ";\n";
    }
}
void pljit::PrintDotVisitor::visit(const pljit::Variable_Dec& dec) {
    int thisnum = number++;
    cout << "\t" << thisnum << " [label=\"variable-declarations\"];\n";
    dec.var->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
    int dlnum = number;
    dec.declist->accept(*this);
    cout << "\t" << thisnum << " -> " << dlnum << ";\n";
    dec.semi->accept(*this);
    cout << "\t" << thisnum << " -> " << number - 1 << ";\n";
}
PrintDotVisitor::PrintDotVisitor() : number(1) {
}
} // namespace pljit
