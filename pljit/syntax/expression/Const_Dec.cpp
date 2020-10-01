//
// Created by wuha on 05.07.20.
//

#include "Const_Dec.hpp"
#include "Error.hpp"
#include <pljit/lex/Separator.hpp>
namespace pljit {
NonTerminal::NonTerminalType Const_Dec::getType() const {
    return NonTerminal::Const_Dec;
}
unique_ptr<NonTerminal> Const_Dec::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Keyword CONST afterwards");
    unique_ptr<LexToken> constsym = lex.next();
    if (constsym->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*constsym).getType() != Keyword::Type::CONST) return make_unique<pljit::Error>(constsym->pos, "Expected a Keyword CONST here");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected  init-declarator-list afterwards");
    unique_ptr<NonTerminal> il = Init_List::parse(lex);
    if (il->getType() == Error) return il; //return error when parsing init list
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Separator ';' here");
    unique_ptr<LexToken> semi = lex.next();
    if (semi->getTokenType() != LexToken::Separator || static_cast<Separator&>(*semi).getType() != Separator::SEMI) return make_unique<pljit::Error>(semi->pos, "Expected a Separator ';' here");
    return make_unique<Const_Dec>(move(constsym), move(il), move(semi));
}
Const_Dec::Const_Dec(unique_ptr<LexToken> con, unique_ptr<NonTerminal> idlist, unique_ptr<LexToken> semi) : constsym(move(con)), initlist(move(idlist)), semi(move(semi)) {
}
void Const_Dec::accept(TreeVisitor& v) const {
    v.visit(*this);
}

} // namespace pljit
