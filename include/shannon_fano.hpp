#pragma once

#include <iostream>
#include <vector>

#include "util.hpp"

namespace shannon_fano {

template <typename Symbol, typename Weight>
double print(std::vector<weighted_symbol<Symbol, Weight>> const& p, size_t l,
             size_t r, codeword c, bool verbose) {
    if (l == r) {
        std::cout << "W(" << p[l].s << ") = " << p[l].w << "; C(" << p[l].s
                  << ") = " << c << std::endl;
        return c.length() * p[l].w;
    }

    size_t pl = l;
    size_t pr = r;
    auto prob_l = p[pl].w;
    auto prob_r = p[pr].w;
    while (true) {
        while (prob_r < prob_l and pr != pl + 1) {
            --pr;
            prob_r += p[pr].w;
        }
        if (pr != pl + 1) {
            ++pl;
            prob_l += p[pl].w;
        } else {
            break;
        }
    }

    if (verbose) {
        std::cout << "partitioning around " << p[pl].s << std::endl;
        for (size_t i = l; i != pl + 1; ++i) {
            std::cout << p[i].s << " ";
        }
        std::cout << "(" << prob_l << ")";
        std::cout << " -- ";
        for (size_t i = pr; i != r + 1; ++i) {
            std::cout << p[i].s << " ";
        }
        std::cout << "(" << prob_r << ")" << std::endl;
    }

    return print(p, l, pl, c + 0, verbose) + print(p, pr, r, c + 1, verbose);
}

template <typename Symbol, typename Weight>
double print(std::vector<weighted_symbol<Symbol, Weight>>& p,
             bool verbose = false) {
    std::sort(p.begin(), p.end(),
              [](auto const& x, auto const& y) { return x.w > y.w; });
    if (verbose) {
        for (auto const& sp : p) {
            std::cout << sp.s << " " << sp.w << "\n";
        }
    }
    codeword c;
    return print(p, 0, p.size() - 1, c, verbose);
}
}  // namespace shannon_fano
