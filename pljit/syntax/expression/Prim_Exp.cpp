//
// Created by wuha on 05.07.20.
//

#include "Prim_Exp.hpp"
#include "Add_Exp.hpp"
#include "Error.hpp"
#include <pljit/lex/Number.hpp>
namespace pljit {

unique_ptr<NonTerminal> pljit::Prim_Exp::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected Primary expression afterwards");
    unique_ptr<LexToken> tmptoken = lex.next();
    switch (tmptoken->getTokenType()) { //next can either be
        case LexToken::Identifer:return make_unique<Prim_Exp>(move(tmptoken));
        case LexToken::Keyword: {
            if (static_cast<Keyword&>(*tmptoken).getType() == Keyword::Type::LeftPrent) {
                unique_ptr<NonTerminal> addexp = Add_Exp::parse(lex);
                if (addexp->getType() == Error) return addexp; //return error
                if (!lex.hasNext())
                    return make_unique<pljit::Error>(tmptoken->pos, "Expected a ')' to match this");
                else {
                    unique_ptr<LexToken> tmprightprent = lex.next();
                    if (static_cast<Keyword&>(*tmprightprent).getType() == Keyword::Type::RightPrent) {
                        return make_unique<Prim_Exp>(move(tmptoken), move(addexp), move(tmprightprent));
                    } else {
                        return make_unique<pljit::Error>(tmptoken->pos, "Expected a ')' to match this");
                    }
                }

            }
            return make_unique<pljit::Error>(tmptoken->pos, "invalid token expected a '(' or a identifer or a literal");
        }
        case LexToken::Number:return make_unique<Prim_Exp>(move(tmptoken));
        default: return make_unique<pljit::Error>(tmptoken->pos, "invalid token expected a '(' or a identifer or a literal"); //none of above is matched
    }

}
Prim_Exp::Prim_Exp(unique_ptr<LexToken> l) : ifadd(false),symbol(move(l)) {
}
Prim_Exp::Prim_Exp(unique_ptr<LexToken> l, unique_ptr<NonTerminal> add, unique_ptr<LexToken> r) : ifadd(true), leftprent(move(l)), addexp(move(add)), rightprent(move(r)) {
}
NonTerminal::NonTerminalType Prim_Exp::getType() const {
    return NonTerminal::Prim_Exp;
}
void Prim_Exp::accept(TreeVisitor& v) const {
    v.visit(*this);
}

} // namespace pljit
