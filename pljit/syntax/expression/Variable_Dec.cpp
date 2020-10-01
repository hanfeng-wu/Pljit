//
// Created by wuha on 05.07.20.
//

#include "Variable_Dec.hpp"
#include "Error.hpp"
#include <pljit/lex/Separator.hpp>
namespace pljit {
unique_ptr<NonTerminal> Variable_Dec::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Keyword VAR afterwards");
    unique_ptr<LexToken> var = lex.next();
    if (var->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*var).getType() != Keyword::Type::VAR) return make_unique<pljit::Error>(var->pos, "Expected a Keyword VAR here");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected  declarator-list afterwards");
    unique_ptr<NonTerminal> dl = Dec_List::parse(lex);
    if (dl->getType() == Error) return dl; //return error when parsing dec list
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Separator ';' here");
    unique_ptr<LexToken> semi = lex.next();
    if (semi->getTokenType() != LexToken::Separator || static_cast<Separator&>(*semi).getType() != Separator::SEMI) return make_unique<pljit::Error>(semi->pos, "Expected a Separator ';' here");
    return make_unique<Variable_Dec>(move(var), move(dl), move(semi));
}
NonTerminal::NonTerminalType Variable_Dec::getType() const {
    return NonTerminal::Variable_Dec;
}
Variable_Dec::Variable_Dec(unique_ptr<LexToken> var, unique_ptr<NonTerminal> dl, unique_ptr<LexToken> semi) : var(move(var)), declist(move(dl)), semi(move(semi)) {
}
void Variable_Dec::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit