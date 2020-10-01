//
// Created by wuha on 21.07.20.
//
#pragma once
#ifndef PLJIT_SEMANTICTREENODE_HPP
#define PLJIT_SEMANTICTREENODE_HPP

#include <cstdint>
#include <pljit/semantic/ASTVisitor.hpp>
#include <memory>
using namespace std;
namespace pljit{
    class AST;
    class SemanticTreeNode {
        public:
        virtual void accept(ASTVisitor&) const = 0;
        virtual ~SemanticTreeNode() = default;

    };
}// namespace pljit

#endif //PLJIT_SEMANTICTREENODE_HPP
