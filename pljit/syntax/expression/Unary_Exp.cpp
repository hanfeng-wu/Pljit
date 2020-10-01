//
// Created by wuha on 05.07.20.
//

#include "Unary_Exp.hpp"
#include "Error.hpp"
namespace pljit {
unique_ptr<NonTerminal> pljit::Unary_Exp::parse(pljit::Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected unary expression afterwards");
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum;
    unique_ptr<LexToken> tmpvorzeichen = lex.next();
    if (tmpvorzeichen->getTokenType() == LexToken::TokenType::Keyword) {
        if (static_cast<Keyword&>(*tmpvorzeichen).getType() == Keyword::Type::MINUS || static_cast<Keyword&>(*tmpvorzeichen).getType() == Keyword::Type::PLUS) { //+ oder -
            unique_ptr<NonTerminal> tmpprimexp = Prim_Exp::parse(lex);
            if (tmpprimexp->getType() == Error) goto out; //doesn't work with sign
            return make_unique<Unary_Exp>(move(tmpvorzeichen), move(tmpprimexp)); //worked
        }
    }
out:
    lex.i = tmpi;
    lex.j = tmpj;
    lex.lnum = tmpln;
    unique_ptr<NonTerminal> tmpprimexp = Prim_Exp::parse(lex);
    if (tmpprimexp->getType() == Error) return tmpprimexp; //doesn't work with prim_Exp, return the error
    return make_unique<Unary_Exp>(move(tmpprimexp)); // parse prim_exp works
}
Unary_Exp::Unary_Exp(unique_ptr<LexToken> l, unique_ptr<NonTerminal> p) : ifsign(true), vorzeichen(move(l)), primexp(move(p)) {
}
Unary_Exp::Unary_Exp(unique_ptr<NonTerminal> p) : ifsign(false), primexp(move(p)) {
}
NonTerminal::NonTerminalType Unary_Exp::getType() const {
    return NonTerminal::Unary_Exp;
}
void Unary_Exp::accept(TreeVisitor& v) const {
    v.visit(*this);
}

} // namespace pljit
