//
// Created by wuha on 05.07.20.
//

#include "Dec_List.hpp"
#include "Error.hpp"
#include <pljit/lex/Separator.hpp>
namespace pljit {
unique_ptr<NonTerminal> Dec_List::parse(Lexer& lex) {
    if (!lex.hasNext()) return make_unique<pljit::Error>(lex.last, "Expected a Identifer afterwards");
    unique_ptr<LexToken> fisrtid = lex.next();
    if (fisrtid->getTokenType() != LexToken::Identifer) return make_unique<pljit::Error>(fisrtid->pos, "Invalid Identifer name, Expected a Identifer here");
    unique_ptr<Dec_List> dl = make_unique<Dec_List>();
    dl->children.push_back(move(fisrtid)); //put the first statement into it
    unique_ptr<LexToken> comma;
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum; //record the index to undo the next()
    while (lex.hasNext() && (comma = lex.next())->getTokenType() == LexToken::Separator && static_cast<Separator&>(*comma).getType() == Separator::COMMA) {
        dl->children.push_back(move(comma)); //push back the ,
        unique_ptr<LexToken> id = lex.next();
        if (id->getTokenType() != LexToken::Identifer) return make_unique<pljit::Error>(id->pos, "Invalid Identifer name, Expected a Identifer here");
        dl->children.push_back(move(id)); //push back the identifer
        tmpi = lex.i;
        tmpj = lex.j;
        tmpln = lex.lnum; //record the index to undo the next()
    }
    lex.i = tmpi;
    lex.j = tmpj;
    lex.lnum = tmpln; //reset the index of lex
    return dl;
}
NonTerminal::NonTerminalType Dec_List::getType() const {
    return NonTerminal::Dec_List;
}
void Dec_List::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit