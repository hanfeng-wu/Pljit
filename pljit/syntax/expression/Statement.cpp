//
// Created by wuha on 12.07.20.
//

#include "Statement.hpp"
#include "Error.hpp"
namespace pljit {
unique_ptr<NonTerminal> Statement::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected Statement afterwards");
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum; //record the index before trying next
    unique_ptr<NonTerminal> assexp = Assign_Exp::parse(lex);
    if (assexp->getType() == Error) { //not Assign_Exp reset index
        lex.i = tmpi;
        lex.j = tmpj;
        lex.lnum = tmpln; //reset the index of lexer
    } else {
        return make_unique<Statement>(move(assexp));
    }
    unique_ptr<LexToken> rttoken = lex.next();
    if (rttoken->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*rttoken).getType() != Keyword::Type::RETURN) return make_unique<pljit::Error>(rttoken->pos, "Expected a Statement here");
    //get a keyword RETURN
    unique_ptr<NonTerminal> addexp = Add_Exp::parse(lex);
    if (addexp->getType() == Error)
        return make_unique<pljit::Error>(rttoken->pos, "Expected a following ADD-expression here");
    else {
        return make_unique<Statement>(move(rttoken), move(addexp));
    }
}
NonTerminal::NonTerminalType Statement::getType() const {
    return NonTerminal::Statement;
}
Statement::Statement(unique_ptr<NonTerminal> assign) : assexp(move(assign)), ifreturn(false) {
}
Statement::Statement(unique_ptr<LexToken> rt, unique_ptr<NonTerminal> addexp) : ifreturn(true), returnToken(move(rt)), addexp(move(addexp)) {
}
void Statement::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit