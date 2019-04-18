#pragma once

#include <iostream>
#include <vector>

#include "util.hpp"

namespace shannon_fano {

template <typename Symbol>
double print(std::vector<symbol_probability<Symbol>> const& p, size_t l,
             size_t r, codeword c, bool verbose) {
    if (l == r) {
        std::cout << "P(" << p[l].s << ") = " << p[l].p << "; C(" << p[l].s
                  << ") = " << c << std::endl;
        return c.length() * p[l].p;
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

    return print(p, l, pl, c + 0, verbose) + print(p, pr, r, c + 1, verbose);
}

template <typename Symbol>
double print(std::vector<symbol_probability<Symbol>>& p, bool verbose = false) {
    std::sort(p.begin(), p.end(),
              [](auto const& x, auto const& y) { return x.p > y.p; });
    if (verbose) {
        for (auto const& sp : p) {
            std::cout << sp.s << " " << sp.p << "\n";
        }
    }
    codeword c;
    return print(p, 0, p.size() - 1, c, verbose);
}
}  // namespace shannon_fano
