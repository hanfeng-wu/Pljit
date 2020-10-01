//
// Created by wuha on 09.07.20.
//

#include "Number.hpp"
#include <cmath>
namespace pljit {
LexToken::TokenType Number::getTokenType() {
    return pljit::LexToken::Number;
}
int64_t Number::getNum() const {
    return num;
}
Number::Number(Position pos, LexToken::TokenType t, std::string_view sv) : LexToken(pos, t) {
    num = 0;
    for (char i : sv) { //convert string_view to int_64
        num *= 10;
        num += (i - 48);
    }
}
void Number::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit
