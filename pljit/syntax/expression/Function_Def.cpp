//
// Created by wuha on 05.07.20.
//

#include "Function_Def.hpp"
#include "Comp_Statement.hpp"
#include <pljit/lex/Separator.hpp>

namespace pljit {
unique_ptr<Function_Def> Function_Def::parse(Lexer& lex) {
    bool para =false, var = false, con = false;
    int tmpi = lex.i;
    int tmpj = lex.j;
    int tmpln = lex.lnum; //record the index to undo the next()
    unique_ptr<NonTerminal> paradec;
    unique_ptr<NonTerminal> vardec;
    unique_ptr<NonTerminal> condec;
    if (!lex.hasNext()) lex.printSyntaxError(lex.last, "Empty Function");
    unique_ptr<LexToken> firstkey = lex.next();
    if (firstkey->getTokenType() == LexToken::Keyword) { //might be PARAM VAR or CONST
        switch (static_cast<Keyword&>(*firstkey).getType()) {
            case Keyword::Type::PARAM: {
                lex.i = tmpi;
                lex.j = tmpj;
                lex.lnum = tmpln; //reset the index of lex
                paradec = Parameter_Dec::parse(lex);
                if (paradec->getType() == Error) {
                    lex.printSyntaxError(static_cast<pljit::Error&>(*paradec));
                }
                para = true;
                if (!lex.hasNext()) lex.printSyntaxError(lex.last, "Expected Statements afterwards");
                tmpi = lex.i;
                tmpj = lex.j;
                tmpln = lex.lnum; //record the index to undo the next()
                unique_ptr<LexToken> key = lex.next(); //to see what the next keyword is
                if (key->getTokenType() == LexToken::Keyword) {
                    if (static_cast<Keyword&>(*key).getType() == Keyword::Type::VAR) goto v;
                    if (static_cast<Keyword&>(*key).getType() == Keyword::Type::CONST) goto c;
                }
                break; //no labels anymore parse compound statement
            }
            case Keyword::Type::VAR: {
            v:
                lex.i = tmpi;
                lex.j = tmpj;
                lex.lnum = tmpln; //reset the index of lex
                vardec = Variable_Dec::parse(lex);
                if (vardec->getType() == Error) {
                    lex.printSyntaxError(static_cast<pljit::Error&>(*vardec));
                }
                var = true;
                if (!lex.hasNext()) lex.printSyntaxError(lex.last, "Expected Statements afterwards");
                tmpi = lex.i;
                tmpj = lex.j;
                tmpln = lex.lnum; //record the index to undo the next()
                unique_ptr<LexToken> key = lex.next(); //to see what the next keyword is
                if (key->getTokenType() == LexToken::Keyword) {
                    if (static_cast<Keyword&>(*key).getType() == Keyword::Type::CONST) goto c; //is next is CONST
                }
                break; //no labels anymore parse compound statement
            }
            case Keyword::Type::CONST: {
            c:
                lex.i = tmpi;
                lex.j = tmpj;
                lex.lnum = tmpln; //reset the index of lex
                condec = Const_Dec::parse(lex);
                if (condec->getType() == Error) {
                    lex.printSyntaxError(static_cast<pljit::Error&>(*condec));
                }
                con = true;
                if (!lex.hasNext()) lex.printSyntaxError(lex.last, "Expected Statements afterwards");
                tmpi = lex.i;
                tmpj = lex.j;
                tmpln = lex.lnum; //record the index to undo the next()
                //break;//goto parse the compound statements
            }
            default:break;
        }
        lex.i = tmpi;
        lex.j = tmpj;
        lex.lnum = tmpln; //reset the index of lex
        unique_ptr<NonTerminal> compound_statements = pljit::Comp_Statement::parse(lex);
        if (compound_statements->getType() == Error) {
            lex.printSyntaxError(static_cast<pljit::Error&>(*compound_statements)); //fail parsing compound statement;
        }
        if (!lex.hasNext()) lex.printSyntaxError(lex.last, "Expected '.' here");
        unique_ptr<LexToken> point = lex.next();
        if (point->getTokenType() != LexToken::Separator || static_cast<Separator&>(*point).getType() != Separator::POINT) lex.printSyntaxError(point->pos, "Expected '.' here");
        unique_ptr<Function_Def> ans = make_unique<Function_Def>(move(compound_statements), move(point));
        if (para) {
            ans->paradec = move(paradec);
            ans->ifpara = true;
        }
        if (var) {
            ans->varadec = move(vardec);
            ans->ifvar = true;
        }
        if (con) {
            ans->constdec = move(condec);
            ans->ifcon = true;
        }
        return ans;
    }
    lex.printSyntaxError(firstkey->pos, "invalid Function definition expected Keyword  'PARAM','VAR','CONST','BEGIN' here");
    exit(1);
}
NonTerminal::NonTerminalType Function_Def::getType() const {
    return NonTerminal::Funtion_Def;
}
Function_Def::Function_Def(unique_ptr<NonTerminal> compstates, unique_ptr<LexToken> point) : ifpara(false), ifvar(false), ifcon(false), comp_states(move(compstates)), point(move(point)) {
}
void Function_Def::accept(TreeVisitor& v) const {
    v.visit(*this);
}
} // namespace pljit