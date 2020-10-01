//
// Created by wuha on 22.07.20.
//

#include "ASTPrintDotVisitor.hpp"
#include "TreeNode/Expression.hpp"
#include "TreeNode/SemanticStatement.hpp"
#include "TreeNode/Function.hpp"
#include <iostream>
using namespace std;
namespace pljit{
    void pljit::ASTPrintDotVisitor::visit(const pljit::AssignExpression& expression) {
        int thisnum = number++;
        cout << "\t" << thisnum << " [label=\"AssignExpression\"];\n";
        cout << "\t" << number++<< " [label=\""<<expression.name<<"\"];\n";
        cout << "\t" << thisnum << " -> " << number -1 << ";\n";
        cout << "\t" << number++<< " [label=\""<<"="<<"\"];\n";
        cout << "\t" << thisnum << " -> " << number -1 << ";\n";
        int expnum = number;
        expression.exp->accept(*this);
        cout << "\t" << thisnum << " -> " << expnum << ";\n";

    }
    void pljit::ASTPrintDotVisitor::visit(const pljit::UnaryExpression& expression) {
        int thisnum = number++;
        cout << "\t" << thisnum << " [label=\"UnaryExpression\"];\n";
        if(expression.sign){//+ then don't have to show the add
            int expnum = number;
            expression.exp->accept(*this);
            cout << "\t" << thisnum << " -> " << expnum << ";\n";
        }else{
            int negnum = number++;
            cout << "\t" << negnum << " [label=\"-\"];\n";
            cout << "\t" << thisnum << " -> " << negnum << ";\n";
            int expnum = number;
            expression.exp->accept(*this);
            cout << "\t" << negnum << " -> " << expnum << ";\n";

        }
    }
    void pljit::ASTPrintDotVisitor::visit(const pljit::PrimExpression& expression) {
        int thisnum = number++;
        cout << "\t" << thisnum << " [label=\"PrimExpression\"];\n";
        int childnum = number;
        switch (expression.getType()) {
            case PrimExpression::Id: {
                cout << "\t" << number++ << " [label=\""<< expression.name<<"\"];\n";
                break;
            }
            case PrimExpression::Num: {
                cout << "\t" << number++ << " [label=\""<< expression.number<<"\"];\n";
                break;
            }
            case PrimExpression::Addexp: {
                expression.addexp->accept(*this);
                break;
            };
        }
        cout << "\t" << thisnum << " -> " << childnum << ";\n";
    }
    void pljit::ASTPrintDotVisitor::visit(const pljit::BinaryExpression& expression) {
        int thisnum = number++;
        cout << "\t" << thisnum << " [label=\"BiaryExpression\"];\n";
        int leftnum = number;
        expression.left->accept(*this);
        cout << "\t" << thisnum << " -> " << leftnum << ";\n";
        int opnum = number++;
        switch (expression.opr) {
            case Keyword::Type::PLUS: {
                cout << "\t" << opnum << " [label=\"+\"];\n";
                break;
            }
            case Keyword::Type::MINUS: {
                cout << "\t" << opnum << " [label=\"-\"];\n";
                break;
            }
            case Keyword::Type::MULTIPLY: {
                cout << "\t" << opnum << " [label=\"*\"];\n";
                break;
            }
            case Keyword::Type::DIVIDE: {
                cout << "\t" << opnum << " [label=\"/\"];\n";
                break;
            }
            default:break;
        }
        cout << "\t" << thisnum << " -> " << opnum << ";\n";
        int rightnum = number;
        expression.right->accept(*this);
        cout << "\t" << thisnum << " -> " << rightnum << ";\n";

    }
    void pljit::ASTPrintDotVisitor::visit(const pljit::ReturnStatement& statement) {
        int thisnum = number++;
        int returnnum = number++;
        cout << "\t" << thisnum << " [label=\"Statement\"];\n";
        cout << "\t" << returnnum << " [label=\"Return\"];\n";
        cout << "\t" << thisnum << " -> " << returnnum << ";\n";
        int addnum = number;
        statement.exp->accept(*this);
        cout << "\t" << thisnum << " -> " << addnum << ";\n";
    }
    void pljit::ASTPrintDotVisitor::visit(const pljit::AssignmentStatement& statement) {
        int thisnum = number++;
        cout << "\t" << thisnum << " [label=\"Statement\"];\n";
        int assnum = number;
        statement.exp->accept(*this);
        cout << "\t" << thisnum << " -> " << assnum << ";\n";

    }
    void pljit::ASTPrintDotVisitor::visit(const pljit::Function& function) {
        cout << "digraph {\n";
        cout << "\t0 [label=\"Function\"];\n";
        for(auto& statement : function.children){
            int num = number;
            statement->accept(*this);
            cout << "\t" << 0 << " -> " << num << ";\n";
        }
        cout << "}\n";
    }
    ASTPrintDotVisitor::ASTPrintDotVisitor() :number(1){
    }
    }// namespace pljit
