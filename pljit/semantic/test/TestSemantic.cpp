//
// Created by wuha on 22.07.20.
//
#include "pljit/semantic/AST.hpp"
#include "pljit/semantic/ASTPrintDotVisitor.hpp"
#include "pljit/semantic/TreeNode/Function.hpp"
#include "pljit/syntax/SyntaxParser.hpp"
#include <pljit/semantic/Evaluator.hpp>
#include <pljit/semantic/Optimizer.hpp>
#include <utility>
#include <gtest/gtest.h>
using namespace pljit;
using namespace std;
TEST(TestSemantic,testprintdot){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "RETURN density * volume\n"
                       "END.");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    ASTPrintDotVisitor  apdv;
    apdv.visit(ast.getRoot());
}
TEST(TestSemantic,testdoubledeclare){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR width;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "RETURN density * -volume\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    ASSERT_DEATH(AST ast(sp),"width is declared twice");

}
TEST(TestSemantic,testuninitassign){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := volume * height * depth;\n"
                       "RETURN density * -volume\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    ASSERT_DEATH(AST ast(sp),"volume is not initialized");
}
TEST(TestSemantic,testconstassign){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "density := width * height * depth;\n"
                       "RETURN density * -volume\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    ASSERT_DEATH(AST ast(sp),"density is Const, Assignment to a Const variable is not allowed");
}
TEST(TestSemantic,testundeclared){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := a * height * depth;\n"
                       "RETURN density * -volume\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    ASSERT_DEATH(AST ast(sp),"a is not defined");
}
TEST(TestSemantic,testmissingreturn){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    ASSERT_DEATH(AST ast(sp),"This Function needs a Return Statement");
}
TEST(TestSemantic,test1divide0){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width / 0;\n"
                       "RETURN 0\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    Evaluator e = Evaluator(ast);
    ASSERT_DEATH(e.evaluate(),"divide by 0");
}
TEST(TestSemantic,testdivide0){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width / (1-1);\n"
                       "RETURN 0\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    Evaluator e = Evaluator(ast);
    ASSERT_DEATH(e.evaluate(),"divide by 0");
}
TEST(TestSemantic,testevaluate){
    Lexer test = Lexer("VAR a;\n"
                       "CONST b = 2, heewoo = 123;\n"
                       "BEGIN\n"
                       "a := heewoo * b;\n"
                       "RETURN a+2\n"
                       "END.");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    Evaluator e = Evaluator(ast);
    ASSERT_EQ(e.evaluate(),248);
}
TEST(TestSemantic,testDeadCodeOptimizer){
    Lexer test = Lexer("VAR a;\n"
                       "CONST b = 1, c = 2;\n"
                       "BEGIN\n"
                       "a := c * b;\n"
                       "RETURN a+2;\n"
                       "a := c*b\n"
                       "END.");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    ASSERT_EQ(3,ast.getRoot().children.size());
    ASTPrintDotVisitor  apdv;
    cout<<"not optimized AST\n";
    apdv.visit(ast.getRoot());
    DeadCodeOptimizer deadCodeOptimizer;
    deadCodeOptimizer.optimize(ast);
    ASSERT_EQ(2,ast.getRoot().children.size());
    cout<<"------------------------------\n";
    cout<<"optimized AST\n";
    apdv.visit(ast.getRoot());
}
TEST(TestSemantic,testConstPropOptimizer1){
    Lexer test = Lexer("PARAM w, h, d;\n"
                       "VAR a;\n"
                       "CONST b = 1, c = 2;\n"
                       "BEGIN\n"
                       "a := c * b;\n"
                       "a := w;\n"
                       "RETURN a+2\n"
                       "END.");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    ASTPrintDotVisitor  apdv;
    cout<<"not optimized AST\n";
    apdv.visit(ast.getRoot());
    ConstPropOptimizer constCodeOptimizer;
    constCodeOptimizer.optimize(ast);
    Expression& assignexp = *static_cast<AssignmentStatement&>(**ast.getRoot().children.begin()).exp;
    Expression& unaryexp = *static_cast<AssignExpression&>(assignexp).exp;
    ASSERT_EQ(2, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(unaryexp).exp).number);///test if c*b is optimized to 2
    cout<<"------------------------------\n";
    cout<<"optimized AST\n";
    apdv.visit(ast.getRoot());
}
TEST(TestSemantic,testConstPropOptimizer2){
    Lexer test = Lexer("PARAM w, h, d;\n"
                       "VAR a;\n"
                       "CONST b = 1, c = 2;\n"
                       "BEGIN\n"
                       "a := c * b;\n"
                       "a := w * b;\n"
                       "RETURN c+2*b\n"
                       "END.");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    ASTPrintDotVisitor  apdv;
    cout<<"not optimized AST\n";
    apdv.visit(ast.getRoot());
    ConstPropOptimizer constCodeOptimizer;
    constCodeOptimizer.optimize(ast);
    auto iter = (ast.getRoot().children.begin());
    Expression& assignexp1 = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp1 = *static_cast<AssignExpression&>(assignexp1).exp;
    ASSERT_EQ(2, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(unaryexp1).exp).number);///test if c * b is optimized to 2
    Expression& assignexp2 = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp2 = *static_cast<AssignExpression&>(assignexp2).exp;
    ASSERT_EQ(Keyword::Type::MULTIPLY, static_cast<BinaryExpression&>(unaryexp2).opr);///test if w*b does not change
    cout<<"------------------------------\n";
    cout<<"optimized AST\n";
    apdv.visit(ast.getRoot());
}
TEST(TestSemantic,testConstPropOptimizer3){
    Lexer test = Lexer("PARAM c;\n"
                       "VAR a,b,d;\n"
                       "BEGIN\n"
                       "a := 2 + 3;\n"
                       "b := a + 4;\n"
                       "a := c + 5;\n"
                       "d := a * 6;\n"
                       "RETURN a\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    ASTPrintDotVisitor  apdv;
    cout<<"not optimized AST\n";
    apdv.visit(ast.getRoot());
    ConstPropOptimizer constCodeOptimizer;
    constCodeOptimizer.optimize(ast);
    auto iter = (ast.getRoot().children.begin());
    Expression& assignexp = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp = *static_cast<AssignExpression&>(assignexp).exp;
    ASSERT_EQ(5, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(unaryexp).exp).number);///test if 2 + 3 is optimized to 5
    Expression& assignexp1 = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp1 = *static_cast<AssignExpression&>(assignexp1).exp;
    ASSERT_EQ(9, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(unaryexp1).exp).number);///test if a + 4 is optimized to 9
    Expression& assignexp2 = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp2 = *static_cast<AssignExpression&>(assignexp2).exp;
    ASSERT_EQ(Keyword::Type::PLUS, static_cast<BinaryExpression&>(unaryexp2).opr);///test if c + 5 does not change
    Expression& assignexp3 = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp3 = *static_cast<AssignExpression&>(assignexp3).exp;
    ASSERT_EQ(Keyword::Type::MULTIPLY, static_cast<BinaryExpression&>(unaryexp3).opr);///test if a * 6 does not change
    cout<<"------------------------------\n";
    cout<<"optimized AST\n";
    apdv.visit(ast.getRoot());
}
TEST(TestSemantic,testConstPropOptimizer4){
    Lexer test = Lexer("PARAM a;\n"
                       "VAR b, c, d;\n"
                       "CONST e = 1;\n"
                       "BEGIN\n"
                       "b := e + 1 / (2 - 1) + 1 -( (4 / 2 * 2 * 1) - 1 );\n"
                       "c := b + e;\n"
                       "d := b + c + e;\n"
                       "RETURN d + 1 * 2- 2 / 1;\n"
                       "a := 233;\n"
                       "RETURN 1\n"
                       "END.");
    SyntaxParser sp = SyntaxParser(test);
    AST ast = AST(sp);
    ASTPrintDotVisitor  apdv;
    cout<<"not optimized AST\n";
    apdv.visit(ast.getRoot());
    DeadCodeOptimizer deadCodeOptimizer;
    deadCodeOptimizer.optimize(ast);
    ConstPropOptimizer constCodeOptimizer;
    constCodeOptimizer.optimize(ast);
    ASSERT_EQ(ast.getRoot().children.size(),4);//the other 2 is optimized by DeadCodeOptimizer;
    auto iter = (ast.getRoot().children.begin());
    Expression& assignexp = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp = *static_cast<AssignExpression&>(assignexp).exp;
    ASSERT_EQ(3, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(unaryexp).exp).number);///test if e + 1 / (2 - 1) + 1 -( (4 / 2 * 2 * 1) - 1 ) is optimized to 3
    Expression& assignexp1 = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp1 = *static_cast<AssignExpression&>(assignexp1).exp;
    ASSERT_EQ(4, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(unaryexp1).exp).number);///test if b + e is optimized to 4
    Expression& assignexp2 = *static_cast<AssignmentStatement&>(*(*iter++)).exp;
    Expression& unaryexp2 = *static_cast<AssignExpression&>(assignexp2).exp;
    ASSERT_EQ(8, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(unaryexp2).exp).number);///test if b + c + e is optimized to 8
    Expression& assignexp3 = *static_cast<ReturnStatement&>(*(*iter++)).exp;
    ASSERT_EQ(8, static_cast<PrimExpression&>(*static_cast<UnaryExpression&>(assignexp3).exp).number);///test if d + 1 * 2- 2 / 1 is optimized to 8
    cout<<"------------------------------\n";
    cout<<"optimized AST\n";
    apdv.visit(ast.getRoot());
}

