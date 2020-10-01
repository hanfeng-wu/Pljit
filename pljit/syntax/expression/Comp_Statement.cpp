//
// Created by wuha on 12.07.20.
//
#include "Comp_Statement.hpp"
#include "Error.hpp"

namespace pljit {
unique_ptr<NonTerminal> Comp_Statement::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Keyword BEGIN afterwards");
    unique_ptr<LexToken> begin = lex.next();
    if (begin->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*begin).getType() != Keyword::Type::BEGIN) return make_unique<pljit::Error>(begin->pos, "Invalid Keyword");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected Statement list here");
    unique_ptr<NonTerminal> sl = Statement_List::parse(lex);
    if (sl->getType() == Error) return sl; //return error when parsing statement list
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Keyword END afterwards");
    unique_ptr<LexToken> end = lex.next();
    if (end->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*end).getType() != Keyword::Type::END) return make_unique<pljit::Error>(end->pos, "Invalid Keyword");
    return make_unique<Comp_Statement>(move(begin), move(sl), move(end));
}
NonTerminal::NonTerminalType Comp_Statement::getType() const {
    return NonTerminal::Comp_Statement;
}
Comp_Statement::Comp_Statement(unique_ptr<LexToken> begin, unique_ptr<NonTerminal> statelist, unique_ptr<LexToken> end) : begin(move(begin)), statelist(move(statelist)), end(move(end)) {
}
void Comp_Statement::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit
