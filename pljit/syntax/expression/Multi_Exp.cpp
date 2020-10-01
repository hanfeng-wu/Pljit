//
// Created by wuha on 05.07.20.
//

#include "Multi_Exp.hpp"
#include <pljit/syntax/expression/Error.hpp>
namespace pljit {
unique_ptr<NonTerminal> pljit::Multi_Exp::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected unary expression afterwards");
    unique_ptr<NonTerminal> unaryexp = Unary_Exp::parse(lex);
    if (unaryexp->getType() == Error) return unaryexp; //error occurred when parsing unaryexp
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum; //record the index before trying next
    if (!lex.hasNext())
        return make_unique<Multi_Exp>(move(unaryexp));
    else {
        unique_ptr<LexToken> oprt = lex.next(); //* or /
        if (oprt->getTokenType() == LexToken::Keyword) {
            if (static_cast<Keyword&>(*oprt).getType() == Keyword::Type::MULTIPLY || static_cast<Keyword&>(*oprt).getType() == Keyword::Type::DIVIDE) { //* oder /
                if (!lex.hasNext()) return make_unique<pljit::Error>(oprt->pos, "Expected Multi-Exp afterwards"); //
                unique_ptr<NonTerminal> multiexp = Multi_Exp::parse(lex);
                if (multiexp->getType() == Error) return multiexp; //error occurred in parsing multi
                return make_unique<Multi_Exp>(move(unaryexp), move(oprt), move(multiexp)); //parse successfully
            } else {
                goto out; //not * or / end of try
            }
        } else {
            goto out; //not key word end of try
        }
    }
out:
    lex.i = tmpi;
    lex.j = tmpj;
    lex.lnum = tmpln; //reset the index of lexer
    return make_unique<Multi_Exp>(move(unaryexp));
}
Multi_Exp::Multi_Exp(unique_ptr<NonTerminal> u) : unexp(move(u)), ifop(false) {
}

Multi_Exp::Multi_Exp(unique_ptr<NonTerminal> u, unique_ptr<LexToken> l, unique_ptr<NonTerminal> m) : unexp(move(u)), ifop(true), opr(move(l)), multiexp(move(m)) {
}
NonTerminal::NonTerminalType Multi_Exp::getType() const {
    return NonTerminal::Multi_Exp;
}
void Multi_Exp::accept(TreeVisitor& v) const {
    v.visit(*this);
}

} // namespace pljit
