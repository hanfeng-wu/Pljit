//
// Created by wuha on 12.07.20.
//

#include "Error.hpp"

namespace pljit {
NonTerminal::NonTerminalType Error::getType() const {
    return NonTerminal::Error;
}
Error::Error(Position p, string s) : pos(p), message(move(s)) {
}
void Error::accept(TreeVisitor&) const {
}

} // namespace pljit
