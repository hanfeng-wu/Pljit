//
// Created by wuha on 12.07.20.
//

#include "Statement_List.hpp"
#include "Error.hpp"
#include <pljit/lex/Separator.hpp>
namespace pljit {
unique_ptr<NonTerminal> Statement_List::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a statement afterwards");
    unique_ptr<NonTerminal> firststate = Statement::parse(lex);
    if (firststate->getType() == Error) return firststate; //Error can't parse the first statement
    unique_ptr<Statement_List> sl = make_unique<Statement_List>();
    sl->children.push_back(move(firststate)); //put the first statement into it
    unique_ptr<LexToken> semi;
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum; //record the index to undo the next()
    while (lex.hasNext() && (semi = lex.next())->getTokenType() == LexToken::Separator && static_cast<Separator&>(*semi).getType() == Separator::SEMI) {
        sl->children.push_back(move(semi)); //push back the ;
        unique_ptr<NonTerminal> state = Statement::parse(lex);
        if (state->getType() == Error) return state; //can't parse a statement after ;
        sl->children.push_back(move(state)); //push back the statement
        tmpi = lex.i;
        tmpj = lex.j;
        tmpln = lex.lnum; //record the index to undo the next()
    }
    lex.i = tmpi;
    lex.j = tmpj;
    lex.lnum = tmpln; //reset the index of lex
    return sl;
}
NonTerminal::NonTerminalType Statement_List::getType() const {
    return NonTerminal::Statement_List;
}
void Statement_List::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit