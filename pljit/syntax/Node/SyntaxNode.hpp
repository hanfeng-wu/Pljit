//
// Created by wuha on 16.07.20.
//
#pragma once
#ifndef PLJIT_SYNTAXNODE_HPP
#define PLJIT_SYNTAXNODE_HPP
#include "pljit/syntax/TreeVisitor.hpp"
namespace pljit {
class SyntaxNode {
    public:
    virtual bool isTerminal() = 0;
    virtual ~SyntaxNode() = default;
    virtual void accept(TreeVisitor&) const = 0;
};
} // namespace pljit

#endif //PLJIT_SYNTAXNODE_HPP
