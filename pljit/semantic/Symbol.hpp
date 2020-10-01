//
// Created by wuha on 21.07.20.
//
#pragma once
#ifndef PLJIT_SYMBOL_HPP
#define PLJIT_SYMBOL_HPP
#include <memory>
#include <pljit/lex/Identifer.hpp>
#include <pljit/lex/Keyword.hpp>
namespace pljit{
    class Symbol {
        public:
        enum SymbolType{
            Para,
            Var,
            Const
        };
        SymbolType getType();
        Symbol(bool,SymbolType);
        Symbol()=default;
        bool ifinit;///determine if the variable is init
        void setValue(int64_t);
        int64_t getValue() const;
        bool getIfStationary() const;
        void setIfStationary(bool);
        Symbol& operator = (const Symbol&) = default;
        Symbol (const Symbol&) = default;
        private:
        SymbolType type;
        int64_t value;
        bool ifStationary;///to determine if a variable currently constant is, not depending on the input variable
    };
}// namespace pljit

#endif //PLJIT_SYMBOL_HPP
