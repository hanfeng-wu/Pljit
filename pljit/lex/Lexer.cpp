//
// Created by wuha on 05.07.20.
//

#include "Lexer.hpp"
#include "Identifer.hpp"
#include "Keyword.hpp"
#include "Number.hpp"
#include "Separator.hpp"
#include <iostream>
#include <string>
#include <utility>
namespace pljit {
Lexer::Lexer(std::string code1):code(std::move(code1)),code_view(code),i(1),j(0),lnum(0),last(0,0){
    //if(code.back()!='\n')code.push_back('\n');
    for(int i=1,j=0;j+i<= static_cast<int>(code.length());){//divide the code by /n
        if(code[j+i-1] == '\n'){
            codelines.push_back(code_view.substr(j,i-1));//'\n inclusive'
            j+=i;
            i=1;
        }else if(j+i ==static_cast<int>(code.length())){
            codelines.push_back(code_view.substr(j,i));//if at end of line there is no \n then this line should also be included
            break;
        }
        else i++;

    }
    last = Position(codelines.size()-1,codelines[codelines.size()-1].size()-1);
}
unique_ptr<LexToken> Lexer::define(Position pos,std::string_view sv) {
    if(sv == "PARAM"){
        return /*std::move*/(make_unique<Keyword>(pos,LexToken::TokenType::Keyword,Keyword::Type::PARAM));
    }else if(sv == "RETURN"){
        return /*std::move*/(make_unique<Keyword>(pos,LexToken::TokenType::Keyword,Keyword::Type::RETURN));
    }
    else if(sv == "VAR"){
        return /*std::move*/(make_unique<Keyword>(pos,LexToken::TokenType::Keyword,Keyword::Type::VAR));
    }
    else if(sv == "CONST"){
        return /*std::move*/(make_unique<Keyword>(pos,LexToken::TokenType::Keyword,Keyword::Type::CONST));
    }
    else if(sv == "BEGIN"){
        return /*std::move*/(make_unique<Keyword>(pos,LexToken::TokenType::Keyword,Keyword::Type::BEGIN));
    }
    else if(sv == "END"){
        return /*std::move*/(make_unique<Keyword>(pos,LexToken::TokenType::Keyword,Keyword::Type::END));
    }else if(validName(sv)){
        return /*std::move*/(make_unique<Identifer>(pos,LexToken::TokenType::Identifer,sv));
    }else if(validNumber(sv)){
        return /*std::move*/(make_unique<Number>(pos,LexToken::TokenType::Number,sv));
    }else{
        cerr<<pos.linenumber<<":"<<pos.index<<": error: invalid indentifer name"<<endl;
        cerr<<codelines[pos.linenumber]<<endl;
        for(unsigned long i= 0;i<pos.index;i++)cerr<<' ';
        cerr<<'^'<<endl;
        return /*std::move*/(make_unique<Identifer>(pos,LexToken::TokenType::Identifer,sv));//invalid Token
    }
}

bool Lexer::validName(std::string_view sv) const{
    for(char i : sv){
        if((i>='a'&&i<='z')||(i>='A'&&i<='Z'));
        else return false;
    }
    return true;
}
bool Lexer::validNumber(std::string_view sv) const {
    for(char i : sv){
        if(i>='0'&&i<='9');
        else return false;
    }
    return true;
}
bool Lexer::hasNext() const {
    return (lnum < static_cast<int>(codelines.size()));
}
std::unique_ptr<LexToken> Lexer::next() {
    unique_ptr<LexToken> ans;
    for(;j+i<= static_cast<int>(codelines[lnum].size());i++){///j:begin of a new token, i: size of new token
        switch (codelines[lnum][j+i-1]) {
            case ' ':{
                if(i>1){// it can't be only a space
                    ans = (define(Position(lnum,j),codelines[lnum].substr(j,i-1)));//' ' not inclusive
                    j+=i;
                    i=1;
                    goto out;
                }
                j++;
                i=0;
                break;//loop again
            }
            case ';':{
                if(i>1){//convert first ab from ab;
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//';' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Separator>(Position(lnum,j),LexToken::TokenType::Separator,Separator::SepType::SEMI)));
                j++;
                i=1;
                goto out;
            }
            case ',':{
                if(i>1){//convert first ab from ab,
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//',' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Separator>(Position(lnum,j),LexToken::TokenType::Separator,Separator::SepType::COMMA)));
                j++;
                i=1;
                goto out;
            }
            case '.':{
                if(i>1){//convert first ab from ab.
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//'.' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Separator>(Position(lnum,j),LexToken::TokenType::Separator,Separator::SepType::POINT)));
                j++;
                i=1;
                goto out;
            }
            case '+':{
                if(i>1){//convert first ab from ab+
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//'+' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::PLUS)));
                j++;
                i=1;
                goto out;
            }
            case '-':{
                if(i>1){//convert first ab from ab-
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//'-' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::MINUS)));
                j++;
                i=1;
                goto out;
            }
            case '*':{
                if(i>1){//convert first ab from ab*
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//'*' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::MULTIPLY)));
                j++;
                i=1;
                goto out;
            }
            case '/':{
                if(i>1){//convert first ab from ab/
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//'/' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::DIVIDE)));
                j++;
                i=1;
                goto out;
            }
            case '(':{
                if(i>1){//convert first ab from ab(
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//'(' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::LeftPrent)));
                j++;
                i=1;
                goto out;
            }
            case ')':{
                if(i>1){//convert first ab from ab)
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//')' not inclusive
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::RightPrent)));
                j++;
                i=1;
                goto out;
            }
            case '=':{
                if(i>1){//convert first ab from ab)
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));
                    j+=i-1;
                    i=1;
                    goto out;
                }
                ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::ConstAssign)));
                j++;
                i=1;
                goto out;
            }
            case ':':{
                if(i>1){//convert first ab from ab)
                    ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));//
                    j+=i-1;
                    i=1;
                    goto out;
                }
                if(j+i+1<=static_cast<int>(codelines[lnum].size()) && codelines[lnum][j+i] == '='){
                    ans = (/*std::move*/(make_unique<Keyword>(Position(lnum,j),LexToken::TokenType::Keyword,Keyword::Type::Assign)));//:=
                    j+=2;
                    i=1;
                    goto out;
                }else{
                    cerr<<lnum<<":"<<j<<": lex error: invalid token name"<<endl;
                    cerr<<codelines[lnum]<<endl;
                    for(int k=0;k<j;k++)cerr<<' ';
                    cerr<<'^'<<endl;
                    exit(1); // exit the programm because := not found
                }
            }
            default:{
                if(i==1){
                    if(validName(codelines[lnum].substr(j,i))||validNumber(codelines[lnum].substr(j,i))){
                        if(j+i == static_cast<int>(codelines[lnum].size())){
                            ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i))));
                            j++;
                            i=1;
                            goto out;
                        }
                    }//still valid check if end of line
                    else{
                        cerr<<lnum<<":"<<j<<": lex error: invalid token name"<<endl;
                        cerr<<codelines[lnum]<<endl;
                        for(int k=0;k<j;k++)cerr<<' ';
                        cerr<<'^'<<endl;
                        exit(1); // exit the programm because := not found
                    }
                }
                else{
                    if(validName(codelines[lnum].substr(j,i))||validNumber(codelines[lnum].substr(j,i))){
                        if(j+i == static_cast<int>(codelines[lnum].size())){
                            ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i))));
                            j+=i;
                            i=1;
                            goto out;
                        }
                    }//still valid check if end of line
                    else{
                        ans = (/*std::move*/(define(Position(lnum,j),codelines[lnum].substr(j,i-1))));
                        j+=i-1;
                        i=1;
                        goto out;
                    }
                }
            }
        }
    }
    out: if(j+i > static_cast<int>(codelines[lnum].size())){
    lnum++;
    j=0;
    i=1;
}
    return ans;

}
//void Lexer::printerror(const Position& pos, const string& message) const {
//    cerr<<pos.linenumber<<":"<<pos.index<<": lexer error: "<<message<<endl;
//    cerr<<codelines[pos.linenumber]<<endl;
//    for(unsigned long i=0;i<pos.index;i++)cerr<<' ';
//    cerr<<'^'<<endl;
//    exit(1);
//}
//void Lexer::printerror(Error& error) const {
//    Position pos = error.pos;
//    string message = error.message;
//    cerr<<pos.linenumber<<":"<<pos.index<<": lexer error: "<<message<<endl;
//    cerr<<codelines[pos.linenumber]<<endl;
//    for(unsigned long i=0;i<pos.index;i++)cerr<<' ';
//    cerr<<'^'<<endl;
//    exit(1);
//
//}
void Lexer::printSemanticError(const Position& pos, string_view name,const string& message) const {
    cerr<<pos.linenumber<<":"<<pos.index<<": semantic error: "<<name<<message<<endl;
    cerr<<codelines[pos.linenumber]<<endl;
    for(unsigned long i=0;i<pos.index;i++)cerr<<' ';
    cerr<<'^'<<endl;
    exit(1);
}
void Lexer::printSemanticError(const Position& pos, const string& message) const {
    cerr<<pos.linenumber<<":"<<pos.index<<": semantic error: "<<message<<endl;
    cerr<<codelines[pos.linenumber]<<endl;
    for(unsigned long i=0;i<pos.index;i++)cerr<<' ';
    cerr<<'^'<<endl;
    exit(1);
}
void Lexer::printArithmeticError(const Position& pos, const string& message) const {
    cerr<<pos.linenumber<<":"<<pos.index<<": arithmetic error: "<<message<<endl;
    cerr<<codelines[pos.linenumber]<<endl;
    for(unsigned long i=0;i<pos.index;i++)cerr<<' ';
    cerr<<'^'<<endl;
    exit(1);
}
void Lexer::printSyntaxError(const Position& pos, const string& message) const {
    cerr<<pos.linenumber<<":"<<pos.index<<": syntax error: "<<message<<endl;
    cerr<<codelines[pos.linenumber]<<endl;
    for(unsigned long i=0;i<pos.index;i++)cerr<<' ';
    cerr<<'^'<<endl;
    exit(1);
}
void Lexer::printSyntaxError(Error& error) const {
    Position pos = error.pos;
    string message = error.message;
    cerr<<pos.linenumber<<":"<<pos.index<<": syntax error: "<<message<<endl;
    cerr<<codelines[pos.linenumber]<<endl;
    for(unsigned long i=0;i<pos.index;i++)cerr<<' ';
    cerr<<'^'<<endl;
    exit(1);
}
}//namespace pljit
