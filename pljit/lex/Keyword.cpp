//
// Created by wuha on 08.07.20.
//

#include "Keyword.hpp"
namespace pljit {
Keyword::Type Keyword::getType() const{
    return type;
}
Keyword::Keyword(Position pos,TokenType t, Keyword::Type type1) : LexToken(pos,t), type(type1) {}
LexToken::TokenType Keyword::getTokenType() {
    return LexToken::Keyword;
}
void Keyword::accept(TreeVisitor& v) const {
    v.visit(*this);
}
}//namespace pljit