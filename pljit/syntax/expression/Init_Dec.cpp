//
// Created by wuha on 12.07.20.
//

#include "Init_Dec.hpp"
#include "Error.hpp"
#include <pljit/lex/Lexer.hpp>
namespace pljit {

unique_ptr<NonTerminal> Init_Dec::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Identifer afterwards");
    unique_ptr<LexToken> identifer = lex.next();
    if (identifer->getTokenType() != LexToken::Identifer) return make_unique<pljit::Error>(identifer->pos, "Expected a Identifer here, invalid Identifer");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a '=' afterwards");
    unique_ptr<LexToken> constAssign = lex.next();
    if (constAssign->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*constAssign).getType() != Keyword::Type::ConstAssign) return make_unique<pljit::Error>(constAssign->pos, "Expected a '=' here");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a literal afterwards");
    unique_ptr<LexToken> literal = lex.next();
    if (literal->getTokenType() != LexToken::Number) return make_unique<pljit::Error>(literal->pos, "Expected a literal here, invalid literal");
    return make_unique<Init_Dec>(move(identifer), move(constAssign), move(literal));
}
NonTerminal::NonTerminalType Init_Dec::getType() const {
    return NonTerminal::Init_Dec;
}
Init_Dec::Init_Dec(unique_ptr<LexToken> id, unique_ptr<LexToken> constassign, unique_ptr<LexToken> number) : identifer(move(id)), ConstAssign(move(constassign)), literal(move(number)) {
}
void Init_Dec::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit