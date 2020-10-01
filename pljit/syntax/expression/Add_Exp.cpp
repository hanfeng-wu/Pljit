//
// Created by wuha on 05.07.20.
//

#include "Add_Exp.hpp"
#include <pljit/syntax/expression/Error.hpp>
namespace pljit {

unique_ptr<NonTerminal> Add_Exp::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected multiplicate expression afterwards");
    unique_ptr<NonTerminal> multiexp = Multi_Exp::parse(lex);
    if (multiexp->getType() == Error) return multiexp; //error occurred when parsing multiexp
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum; //record the index before trying next
    if (!lex.hasNext())
        return make_unique<Add_Exp>(move(multiexp));
    else {
        unique_ptr<LexToken> oprt = lex.next(); //+ or -
        if (oprt->getTokenType() == LexToken::Keyword) {
            if (static_cast<Keyword&>(*oprt).getType() == Keyword::Type::PLUS || static_cast<Keyword&>(*oprt).getType() == Keyword::Type::MINUS) { //+ oder -
                if (!lex.hasNext()) return make_unique<pljit::Error>(oprt->pos, "Expected Add_Exp afterwards"); //
                unique_ptr<NonTerminal> addexp = Add_Exp::parse(lex);
                if (addexp->getType() == Error) return addexp; //error occurred in parsing add_exp
                return make_unique<Add_Exp>(move(multiexp), move(oprt), move(addexp)); //parse successfully
            } else {
                goto out; //not + or - end of try
            }
        } else {
            goto out; //not key word end of try
        }
    }
out:
    lex.i = tmpi;
    lex.j = tmpj;
    lex.lnum = tmpln; //reset the index of lexer
    return make_unique<Add_Exp>(move(multiexp));
}
NonTerminal::NonTerminalType Add_Exp::getType() const {
    return NonTerminal::Add_Exp;
}
Add_Exp::Add_Exp(unique_ptr<NonTerminal> multi) : multiexp(move(multi)), ifadd(false) {
}
pljit::Add_Exp::Add_Exp(unique_ptr<NonTerminal> multi, unique_ptr<LexToken> sign, unique_ptr<NonTerminal> addexp) : multiexp(move(multi)), ifadd(true), opr(move(sign)), addexp(move(addexp)) {
}
void Add_Exp::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit
