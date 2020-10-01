//
// Created by wuha on 05.07.20.
//

#include "Identifer.hpp"
namespace pljit {
Identifer::Identifer(Position pos,TokenType t, std::string_view name) : LexToken(pos,t), name(name) {}
std::string_view Identifer::getName() const {
    return name;
}
LexToken::TokenType Identifer::getTokenType() {
    return LexToken::Identifer;
}
void Identifer::accept(TreeVisitor& v) const {
    v.visit(*this);
}
}//namespace pljit