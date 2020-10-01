//
// Created by wuha on 05.07.20.
//

#include "Separator.hpp"
namespace pljit {
Separator::SepType Separator::getType() const{
    return type;
}
Separator::Separator(Position pos,TokenType t, Separator::SepType type):LexToken(pos,t),type(type) {}
LexToken::TokenType Separator::getTokenType() {
    return LexToken::Separator;
}
void Separator::accept(TreeVisitor& v) const {
    v.visit(*this);
}
}//namespace pljit
