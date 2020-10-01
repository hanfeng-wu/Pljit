//
// Created by wuha on 08.07.20.
//

#include "LexToken.hpp"
namespace pljit {
LexToken::LexToken(Position pos, TokenType t):pos(pos),tokenType(t) {}
LexToken::~LexToken() {
    pos.~Position();
}
bool LexToken::isTerminal() {
    return true;
}
}//namespace pljit
