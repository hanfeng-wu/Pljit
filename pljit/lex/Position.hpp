//
// Created by wuha on 08.07.20.
//
#pragma once
#ifndef PLJIT_POSITION_HPP
#define PLJIT_POSITION_HPP
#include <cstdlib>
#include <string>
using namespace std;
namespace pljit {

class Position {
    public:
    Position(unsigned long , unsigned long );
    unsigned long linenumber;
    unsigned long index;
    Position& operator=(const Position&) = default;
    Position(const Position&) = default;
};
} // namespace pljit

#endif //PLJIT_POSITION_HPP
