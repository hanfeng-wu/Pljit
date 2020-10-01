//
// Created by wuha on 21.07.20.
//

#include "Symbol.hpp"
namespace pljit{
    pljit::Symbol::SymbolType pljit::Symbol::getType() {
        return type;
    }
    Symbol::Symbol(bool ifinit, Symbol::SymbolType type):ifinit(ifinit),type(type),value(0),ifStationary(type==Const || type == Var) {
    }
    void Symbol::setValue(int64_t v) {
        value = v;
    }
    int64_t Symbol::getValue() const {
        return value;
    }
    bool Symbol::getIfStationary() const {
        return ifStationary;
    }
    void Symbol::setIfStationary(bool ifStationary) {
        this->ifStationary = ifStationary;
    }
    }// namespace pljit