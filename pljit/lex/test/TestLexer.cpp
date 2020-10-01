//
// Created by wuha on 12.07.20.
//
#include "pljit/lex/Lexer.hpp"
#include <pljit/lex/Identifer.hpp>
#include <pljit/lex/Number.hpp>
#include <pljit/lex/Separator.hpp>
#include <utility>
#include <gtest/gtest.h>
using namespace pljit;
using namespace std;
TEST(TestLexer,numbers2){
    Lexer test = Lexer("1 2 3 4 5 6 7 8 9 10\n");
    int64_t i =1;
    unique_ptr<LexToken> tmp;
    while(test.hasNext()){
        tmp = test.next();
        ASSERT_EQ(LexToken::TokenType::Number,tmp->getTokenType());
        Number n = static_cast<Number&>(*tmp);
        ASSERT_EQ(n.getNum(),i++);
    }
    ASSERT_EQ(i,11);
}
TEST(TestLexer,param){
    Lexer test = Lexer("PARAM a,b .\n");
    int64_t i =0;
    unique_ptr<LexToken> tmp;
    while(test.hasNext()){
        tmp = test.next();
        switch (i++) {
            case 0: {
                ASSERT_EQ(LexToken::TokenType::Keyword, tmp->getTokenType());
                Keyword n = static_cast<Keyword&>(*tmp);
                ASSERT_EQ(n.getType(), Keyword::Type::PARAM);
                break;
            };
            case 1:{
                ASSERT_EQ(LexToken::TokenType::Identifer, tmp->getTokenType());
                Identifer n = static_cast<Identifer&>(*tmp);
                ASSERT_EQ(n.getName(), "a");
                break;
            }
            case 2:{
                ASSERT_EQ(LexToken::TokenType::Separator, tmp->getTokenType());
                Separator n = static_cast<Separator&>(*tmp);
                ASSERT_EQ(n.getType(), Separator::SepType::COMMA);
                break;
            }
            case 3:{
                ASSERT_EQ(LexToken::TokenType::Identifer, tmp->getTokenType());
                Identifer n = static_cast<Identifer&>(*tmp);
                ASSERT_EQ(n.getName(), "b");
                break;
            }
            case 4:{
                ASSERT_EQ(LexToken::TokenType::Separator, tmp->getTokenType());
                Separator n = static_cast<Separator&>(*tmp);
                ASSERT_EQ(n.getType(), Separator::SepType::POINT);
                break;
            }
        }
    }
    ASSERT_EQ(i,5);
}
TEST(TestLexer,mixtest1){
    Lexer test = Lexer("PARAM w, h, d;\n"
                       "VAR a;\n"
                       "CONST b = 1, c = 2;\n"
                       "BEGIN\n"
                       "a := c * b;\n"
                       "a := a+w;\n"
                       "RETURN w+h+d+a+2\n"
                       "END.\n");
    int i=0;
    while(test.hasNext()){
        test.next();
        i++;
    }
    ASSERT_EQ(44,i);
}
TEST(TestLexer,mixtest2){
    Lexer test = Lexer("PARAMAwda 1 2 23 ab END ..");
    int i=0;
    while(test.hasNext()){
        test.next();
        i++;
    }
    ASSERT_EQ(8,i);
}
TEST(TestLexer,testerror){
    Lexer test = Lexer("PARAMAwda_1 1 2 23 ab END ..");
    test.next();
    ASSERT_DEATH(test.next(),"invalid token name");
}
