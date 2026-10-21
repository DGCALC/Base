//
// Created by Lucius Schoenbaum on 3/13/22.
//

/*
 * DGCALC.h
 *
 * Some basic things that I find useful practically everywhere.
 *
 * Provides:
 * - selected size types with readable names
 * - IPoint<dim>
 * - ipow2 constexpr
 * - ipow constexpr
 * - igeom constexpr
 * - bit-fiddling constexpr
 * - popcount, popsign
 * - "simple" text substitution
 *
 *
 */

#pragma once


#include <cstdint>
#include <cassert>
#include <string>


namespace DGCALC {

// logsize
using logsize_t = int_fast8_t;

// size type
using size_t = std::size_t;

//@ an internally consistent npos value
static const size_t npos = (size_t)(-1);

// integer tuple
template <size_t dim, typename itype = size_t>
struct IPoint {

    static constexpr size_t length = dim;

    itype i[dim];

    // An IPoint that just forwards the indices
    static IPoint idxs() {
        IPoint out;
        for (auto idx = 0; idx < dim; ++idx) {
            out.i[idx] = idx;
        }
        return out;
    }

    // An IPoint consisting of a value
    // e.g., val = 1, dim = 3 ==> {1,1,1}
    static IPoint constant(itype val) {
        IPoint out;
        for (auto idx = 0; idx < dim; ++idx) {
            out.i[idx] = val;
        }
        return out;
    }

    // Bracket notation
    size_t & operator[](size_t ii) {
        return i[ii];
    }

    const size_t & operator[](size_t ii) const {
        return i[ii];
    }

    std::string str() const {
        std::string out = "(";
        for (int ii = 0; ii < dim-1; ++ii) {
            out += std::to_string(i[ii]) + ", ";
        }
        out += std::to_string(i[dim-1]) + ")";
        return out;
    }

};

template <typename T>
static constexpr T max(T& a, T& b) {
    return ((a > b) ? a : b);
}
template <typename T>
static constexpr T min(T& a, T& b) {
    return ((a < b) ? a : b);
}

// integer log base 2
template <typename logitype, typename itype>
static constexpr logitype ilog2(itype n) {
    if (n <= 0) return -1;
    if (n <= 2) return n-1;
    logitype out = sizeof(itype)*8;
    while ((n >> --out) == 0);
    return out;
}

// integer power of 2
template <typename itype, typename logitype>
static constexpr itype ipow2(logitype n) {
    return ((itype)1 << n);
}

// integer power
template <typename itype, typename logitype>
static constexpr itype ipow(logitype base, logitype n) {
    if (n == 0) return (itype)1;
    itype y = (itype)1;
    logitype dec = n;
    while (dec-- > 0) {
        y = y * base;
    }
    return y;
}

// integer geometric series sum r^n from N to N0, inclusive
template <typename itype>
static constexpr itype igeom(itype r, itype N, itype N0 = 0) {
    itype out =  ipow<itype>(r, N+1);
    out -= ipow<itype>(r, N0);
    out /= (r - 1);
    return out;
}

// swap two X's
template <typename X>
static void swap(X & a, X & b) {
    X c = a;
    a = b;
    b = c;
}


// Bit Fiddling

template <typename itype>
static constexpr itype get_bit(itype N, itype i) {
    return ((N >> i) & (itype)1);
}

template <typename itype>
static constexpr void clear_bit(itype & N, itype i) {
    N &= ~((itype)1 << i);
}

template <typename itype>
static constexpr void set_bit(itype & N, itype i) {
    N |= ((itype)1 << i);
}

template <typename itype>
static constexpr void toggle_bit(itype & N, itype i) {
    N ^= ((itype)1 << i);
}

template <typename itype>
static constexpr bool ispow2(itype & N) {
    return !(N & (N - 1));
}

// after C++20: return std::popcount(j);
// on many architectures: POPCNT
template <typename itype>
static constexpr itype popcount(itype N) {
    itype out = 0;
    for (itype i = 0; i < 8*sizeof(itype); ++i) {
        out += get_bit(N, i);
    }
    return out;
}

// the popsign, defined as (-1)^popcount(N)
template <typename itype>
static constexpr int popsign(itype N) {
    return (get_bit(popcount(N), itype(0)))? -1: 1;
}


template <typename itype>
static constexpr itype subi(itype x, size_t low, size_t high) {
    return ((~(0) << high) & x) >> low;
}

// C++ std::size_t can be expected to be the architecture address size.
static constexpr size_t get_sign_bit(size_t N) {
    return ((N >> (sizeof(std::size_t)*8 - (size_t)1) & (size_t)1));
}

static constexpr int64_t get_sign_bit_LL(int64_t N) {
    return ((N >> 63) & 1LL);
}

static constexpr uint64_t get_sign_bit_ULL(uint64_t N) {
    return ((N >> 63) & 1ULL);
}

// string helper method: "simple" substitution
// Definition: replace all occurences of [pattern] with [suband] in [subee].
// ...just a simple tool to do a simple thing without any 1970's contraptions.
void ssub(std::string & subee, const std::string & pattern, const std::string & suband);

}
