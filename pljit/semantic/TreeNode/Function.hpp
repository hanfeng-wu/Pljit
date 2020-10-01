//
// Created by wuha on 05.07.20.
//
#pragma once
#ifndef PLJIT_FUNCTION_HPP
#define PLJIT_FUNCTION_HPP

#include "SemanticTreeNode.hpp"
#include "SemanticStatement.hpp"
#include <memory>
#include <pljit/lex/Keyword.hpp>
#include <pljit/lex/Lexer.hpp>
using namespace std;
namespace pljit{
    class Function : public SemanticTreeNode {
        public:
        list<unique_ptr<SemanticStatement>> children;
        Function() = default;
        void accept(ASTVisitor&) const override;
        ~Function() override = default;
        int64_t evaluate(unordered_map<string_view,Symbol>&) const;

    };
}// namespace pljit

#endif //PLJIT_FUNCTION_HPP
