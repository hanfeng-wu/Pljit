//
// Created by wuha on 05.07.20.
//

#include "Assign_Exp.hpp"
#include <pljit/syntax/expression/Error.hpp>
namespace pljit {

unique_ptr<NonTerminal> Assign_Exp::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected Assignment operation afterwards");
    unique_ptr<LexToken> identifer = lex.next();
    if (identifer->getTokenType() != LexToken::Identifer) return make_unique<pljit::Error>(identifer->pos, "Expected identifer here");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected ':=' afterwards");
    unique_ptr<LexToken> assign = lex.next();
    if (assign->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*assign).getType() != Keyword::Type::Assign) lex.printSyntaxError(assign->pos, "Expected ':=' here");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected additive expression afterwards");
    unique_ptr<NonTerminal> addexp = Add_Exp::parse(lex);
    if (addexp->getType() == Error) lex.printSyntaxError(static_cast<class Error&>(*addexp));
    return make_unique<Assign_Exp>(move(identifer), move(assign), move(addexp));
}
NonTerminal::NonTerminalType Assign_Exp::getType() const {
    return NonTerminal::Assign_Exp;
}
Assign_Exp::Assign_Exp(unique_ptr<LexToken> identifer, unique_ptr<LexToken> assign, unique_ptr<NonTerminal> addexp) : identifer(move(identifer)), assign(move(assign)), addexp(move(addexp)) {
}
void Assign_Exp::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit