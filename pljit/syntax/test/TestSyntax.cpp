//
// Created by wuha on 12.07.20.
//
#include "pljit/lex/Lexer.hpp"
#include "pljit/syntax/expression/Prim_Exp.hpp"
#include <pljit/lex/Identifer.hpp>
#include <pljit/lex/Number.hpp>
#include <pljit/lex/Separator.hpp>
#include <pljit/syntax/Node/NonTerminal.hpp>
#include <pljit/syntax/PrintDotVisitor.hpp>
#include <pljit/syntax/SyntaxParser.hpp>
#include <pljit/syntax/expression/Comp_Statement.hpp>
#include <pljit/syntax/expression/Function_Def.hpp>
#include <pljit/syntax/expression/Statement.hpp>
#include <pljit/syntax/expression/Statement_List.hpp>
#include <utility>
#include <gtest/gtest.h>
using namespace pljit;
using namespace std;
TEST(TestSyntax,testPrim_Exp1){
    Lexer test = Lexer("a\n");
    unique_ptr<NonTerminal> primexp = Prim_Exp::parse(test);
    cout<<primexp->getType()<<endl;
    ASSERT_EQ(primexp->getType(),NonTerminal::NonTerminalType::Prim_Exp);
}
TEST(TestSyntax,testPrim_Exp2){
    Lexer test = Lexer("(a+b)\n");
    unique_ptr<NonTerminal> primexp = Prim_Exp::parse(test);
    ASSERT_EQ(primexp->getType(),NonTerminal::NonTerminalType::Prim_Exp);
    ASSERT_TRUE(static_cast<Prim_Exp&>(*primexp).ifadd);
}
TEST(TestSyntax,testAssign1){
    Lexer test = Lexer("a := a+b\n");
    unique_ptr<NonTerminal> ass = Assign_Exp::parse(test);
    ASSERT_EQ(ass->getType(),NonTerminal::NonTerminalType::Assign_Exp);
}
TEST(TestSyntax,testAssign2){
    Lexer test = Lexer("a := -a + 1\n");
    unique_ptr<NonTerminal> ass = Assign_Exp::parse(test);
    ASSERT_EQ(ass->getType(),NonTerminal::NonTerminalType::Assign_Exp);
}
TEST(TestSyntax,testAssign3){
    Lexer test = Lexer("a := -a + (-a * 5 + -b)\n");
    unique_ptr<NonTerminal> ass = Assign_Exp::parse(test);
    ASSERT_EQ(ass->getType(),NonTerminal::NonTerminalType::Assign_Exp);
}
TEST(TestSyntax,testStatement1){
    Lexer test = Lexer("RETURN a+b\n");
    unique_ptr<NonTerminal> st = Statement::parse(test);
    ASSERT_EQ(st->getType(),NonTerminal::NonTerminalType::Statement);
    ASSERT_TRUE(static_cast<Statement&>(*st).ifreturn);
}
TEST(TestSyntax,testStatement2){
    Lexer test = Lexer("a:= a+b\n");
    unique_ptr<NonTerminal> st = Statement::parse(test);
    ASSERT_EQ(st->getType(),NonTerminal::NonTerminalType::Statement);
    ASSERT_FALSE(static_cast<Statement&>(*st).ifreturn);
}
TEST(TestSyntax,testStatement_list){
    Lexer test = Lexer("a:= a+b ; b:=a+b\n");
    unique_ptr<NonTerminal> sl = Statement_List::parse(test);
    ASSERT_EQ(sl->getType(),NonTerminal::NonTerminalType::Statement_List);
    ASSERT_EQ(static_cast<Statement_List&>(*sl).children.size(),3);
}
TEST(TestSyntax,testStatement_list_Error){
    Lexer test = Lexer("a:= a+b ; b:=a+b ;\n");
    unique_ptr<NonTerminal> sl = Statement_List::parse(test);
    ASSERT_EQ(sl->getType(),NonTerminal::NonTerminalType::Error);
}
TEST(TestSyntax,testComp_Statement){
    Lexer test = Lexer("BEGIN a:= a+b ; b:=a+b END\n");
    unique_ptr<NonTerminal> cs = Comp_Statement::parse(test);
    ASSERT_EQ(cs->getType(),NonTerminal::NonTerminalType::Comp_Statement);
    ASSERT_EQ(static_cast<Statement_List&>(*(static_cast<Comp_Statement&>(*cs).statelist)).children.size(),3);
}
TEST(TestSyntax,testInit_Dec){
    Lexer test = Lexer("ab = 123\n");
    unique_ptr<NonTerminal> id = Init_Dec::parse(test);
    ASSERT_EQ(id->getType(),NonTerminal::NonTerminalType::Init_Dec);
}
TEST(TestSyntax,testInit_List){
    Lexer test = Lexer("ab = 123 , a = 123 , b=2\n");
    unique_ptr<NonTerminal> il = Init_List::parse(test);
    ASSERT_EQ(il->getType(),NonTerminal::NonTerminalType::Init_List);
    ASSERT_EQ(static_cast<Init_List&>(*il).children.size(),5);
}
TEST(TestSyntax,testDec_List){
    Lexer test = Lexer("ab ,a ,b\n");
    unique_ptr<NonTerminal> dl = Dec_List::parse(test);
    ASSERT_EQ(dl->getType(),NonTerminal::NonTerminalType::Dec_List);
    ASSERT_EQ(static_cast<Dec_List&>(*dl).children.size(),5);
}
TEST(TestSyntax,testconstantdeclarations){
    Lexer test = Lexer("CONST ab = 123 , a = 123 , b=2;\n");
    unique_ptr<NonTerminal> cd = Const_Dec::parse(test);
    ASSERT_EQ(cd->getType(),NonTerminal::NonTerminalType::Const_Dec);
    ASSERT_EQ(static_cast<Init_List&>(*(static_cast<Const_Dec&>(*cd).initlist)).children.size(),5);
}
TEST(TestSyntax,testVariabledeclarations){
    Lexer test = Lexer("VAR ab  , a  , b;\n");
    unique_ptr<NonTerminal> vd = Variable_Dec::parse(test);
    ASSERT_EQ(vd->getType(),NonTerminal::NonTerminalType::Variable_Dec);
    ASSERT_EQ(static_cast<Dec_List&>(*(static_cast<Variable_Dec&>(*vd).declist)).children.size(),5);
}
TEST(TestSyntax,testParamdeclarations){
    Lexer test = Lexer("PARAM ab  , a  , b;\n");
    unique_ptr<NonTerminal> pd = Parameter_Dec::parse(test);
    ASSERT_EQ(pd->getType(),NonTerminal::NonTerminalType::Parameter_Dec);
    ASSERT_EQ(static_cast<Dec_List&>(*(static_cast<Parameter_Dec&>(*pd).declist)).children.size(),5);
}
TEST(TestSyntax,testFunctionDef){
    Lexer test = Lexer("PARAM ab  , a  , b;VAR ab  , a  , b;CONST ab = 123 , a = 123 , b=2;BEGIN a:= a+b ; b:=a+b END.\n");
    unique_ptr<NonTerminal> fd = Function_Def::parse(test);
    ASSERT_EQ(fd->getType(),NonTerminal::NonTerminalType::Funtion_Def);
    ASSERT_TRUE(static_cast<Function_Def&>(*fd).ifpara);
    ASSERT_TRUE(static_cast<Function_Def&>(*fd).ifvar);
    ASSERT_TRUE(static_cast<Function_Def&>(*fd).ifcon);
}
TEST(TestSyntax,testsyntaxerror1){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume\n"
                       ";\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "RETURN density * volume\n"
                       "END\n");
    ASSERT_DEATH(Function_Def::parse(test),"syntax error");
}
TEST(TestSyntax,testsyntaxerror2){
    Lexer test = Lexer("PARA width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "RETURN density * volume\n"
                       "END.\n");
    ASSERT_DEATH(Function_Def::parse(test),"syntax error: invalid Function definition expected Keyword  'PARAM','VAR','CONST','BEGIN' here");

}
TEST(TestSyntax,testinvalidToken){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "width := RETURN;\n"
                       "RETURN 1"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    ASSERT_DEATH(sp.parse(),"invalid token");
}
TEST(TestSyntax,testinvalidassign){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "width RETURN volume;\n"
                       "RETURN 1\n"
                       "END.\n");
    SyntaxParser sp = SyntaxParser(test);
    ASSERT_DEATH(sp.parse(),"Expected ':=' here");
}
TEST(TestSyntax,testPrintvisitor){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "RETURN density * volume\n"
                       "END.\n");
    unique_ptr<NonTerminal> fd = Function_Def::parse(test);
    PrintDotVisitor a;
    fd->accept(a);

}
TEST(TestSyntax,testsyntaxerror3){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONT density = 2400;\n"
                       "BEGIN\n"
                       "volume := width * height * depth;\n"
                       "RETURN density * volume\n"
                       "END.\n");
    ASSERT_DEATH(Function_Def::parse(test),"Invalid Keyword");
}
TEST(TestSyntax,testsyntaxerror4){
    Lexer test = Lexer("PARAM width, height, depth;\n"
                       "VAR volume;\n"
                       "CONST density = 2400;\n"
                       "BEGIN\n"
                       "END.\n");
    ASSERT_DEATH(Function_Def::parse(test),"Expected a Statement here");
}


