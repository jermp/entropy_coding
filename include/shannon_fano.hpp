#pragma once

#include <iostream>
#include <vector>

namespace shannon_fano {

typedef uint32_t codeword_type;
typedef float prob_type;

template <typename Symbol>
struct symbol_probability {
    symbol_probability(Symbol s, prob_type p) : s(s), p(p) {}
    Symbol s;
    prob_type p;
};

struct codeword {
    codeword() : m_pos(0), m_bits(0) {}

    void append(bool bit) {
        m_bits |= codeword_type(bit) << m_pos++;
    }

    codeword operator+(bool bit) {
        codeword x = *this;
        x.append(bit);
        return x;
    }

    codeword operator=(codeword const& rhs) {
        codeword x;
        x.m_pos = rhs.m_pos;
        x.m_bits = rhs.m_bits;
        return x;
    }

    friend std::ostream& operator<<(std::ostream& os, codeword const& c) {
        codeword_type b = c.m_bits;
        for (uint32_t p = 0; p != c.m_pos; ++p) {
            os << (b & 1);
            b >>= 1;
        }
        return os;
    }

    uint32_t m_pos;
    codeword_type m_bits;
};

template <typename Symbol>
void print(std::vector<symbol_probability<Symbol>>& p, size_t l, size_t r,
           bool verbose = false) {
    std::sort(p.begin(), p.end(),
              [](auto const& x, auto const& y) { return x.p > y.p; });
    if (verbose) {
        for (auto const& sp : p) {
            std::cout << sp.s << " " << sp.p << "\n";
        }
    }

    codeword c;
    print(p, l, r, c, verbose);
}

template <typename Symbol>
void print(std::vector<symbol_probability<Symbol>> const& p, size_t l, size_t r,
           codeword c, bool verbose) {
    if (l == r) {
        std::cout << "P(" << p[l].s << ") = " << p[l].p << "; C(" << p[l].s
                  << ") = " << c << std::endl;
        return;
    }

    size_t pl = l;
    size_t pr = r;
    float prob_l = p[pl].p;
    float prob_r = p[pr].p;
    while (true) {
        while (prob_r < prob_l and pr != pl + 1) {
            --pr;
            prob_r += p[pr].p;
        }
        if (pr != pl + 1) {
            ++pl;
            prob_l += p[pl].p;
        } else {
            break;
        }
    }

    if (verbose) {
        std::cout << "partitioning around " << p[pl].s << std::endl;
        for (size_t i = l; i != pl + 1; ++i) {
            std::cout << p[i].s << " ";
        }
        std::cout << " -- ";
        for (size_t i = pr; i != r + 1; ++i) {
            std::cout << p[i].s << " ";
        }
        std::cout << std::endl;
    }

    print(p, l, pl, c + 0, verbose);
    print(p, pr, r, c + 1, verbose);
}
}  // namespace shannon_fano
