//
// Created by wuha on 05.07.20.
//

#include "Init_List.hpp"
#include "Error.hpp"
#include <pljit/lex/Separator.hpp>
namespace pljit {
unique_ptr<NonTerminal> Init_List::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Init declarator afterwards");
    unique_ptr<NonTerminal> firstdec = Init_Dec::parse(lex);
    if (firstdec->getType() == Error) return firstdec; //Error can't parse the first init_Dec
    unique_ptr<Init_List> il = make_unique<Init_List>();
    il->children.push_back(move(firstdec)); //put the first init_dec into it
    unique_ptr<LexToken> comma;
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum; //record the index to undo the next()
    while (lex.hasNext() && (comma = lex.next())->getTokenType() == LexToken::Separator && static_cast<Separator&>(*comma).getType() == Separator::COMMA) {
        il->children.push_back(move(comma)); //push back the ,
        unique_ptr<NonTerminal> initdec = Init_Dec::parse(lex);
        if (initdec->getType() == Error) return initdec; //can't parse a init_dec after ;
        il->children.push_back(move(initdec)); //push back the initdec
        tmpi = lex.i;
        tmpj = lex.j;
        tmpln = lex.lnum; //record the index to undo the next()
    }
    lex.i = tmpi;
    lex.j = tmpj;
    lex.lnum = tmpln; //reset the index of lex
    return il;
}
NonTerminal::NonTerminalType Init_List::getType() const {
    return NonTerminal::Init_List;
}
void Init_List::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit