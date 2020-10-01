//
// Created by wuha on 05.07.20.
//

#include "Parameter_Dec.hpp"
#include "Error.hpp"
#include <pljit/lex/Separator.hpp>
namespace pljit {
unique_ptr<NonTerminal> Parameter_Dec::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Keyword PARAM afterwards");
    unique_ptr<LexToken> param = lex.next();
    if (param->getTokenType() != LexToken::Keyword || static_cast<Keyword&>(*param).getType() != Keyword::Type::PARAM) return make_unique<pljit::Error>(param->pos, "Expected a Keyword PARAM here");
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected  declarator-list afterwards");
    unique_ptr<NonTerminal> dl = Dec_List::parse(lex);
    if (dl->getType() == Error) return dl; //return error when parsing dec list
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Separator ';' here");
    unique_ptr<LexToken> semi = lex.next();
    if (semi->getTokenType() != LexToken::Separator || static_cast<Separator&>(*semi).getType() != Separator::SEMI) return make_unique<pljit::Error>(static_cast<class Dec_List&>(*dl).children.back()->pos, "Expected a Separator ';' after this");
    return make_unique<Parameter_Dec>(move(param), move(dl), move(semi));
}
NonTerminal::NonTerminalType Parameter_Dec::getType() const {
    return NonTerminal::Parameter_Dec;
}
Parameter_Dec::Parameter_Dec(unique_ptr<LexToken> param, unique_ptr<NonTerminal> dl, unique_ptr<LexToken> semi) : param(move(param)), declist(move(dl)), semi(move(semi)) {
}
void Parameter_Dec::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit