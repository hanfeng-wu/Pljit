//
// Created by wuha on 21.07.20.
//

#include "SyntaxParser.hpp"
namespace pljit{
    pljit::SyntaxParser::SyntaxParser(pljit::Lexer& lex):lex(lex) {
    }
    unique_ptr<Function_Def> SyntaxParser::parse() {
        return Function_Def::parse(lex);
    }
}// namespace pljit
