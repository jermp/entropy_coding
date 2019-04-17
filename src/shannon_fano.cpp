#include <algorithm>
#include <fstream>
#include <iostream>

#include "../include/shannon_fano.hpp"

int main(int argc, char** argv) {
    int mandatory = 1 + 1;
    if (argc < mandatory) {
        std::cerr << argv[0] << " input_filename" << std::endl;
        return 1;
    }

    using namespace shannon_fano;

    char const* input_filename = argv[1];
    std::vector<symbol_probability<char>> p;
    size_t n = 0;
    {
        std::ifstream in(input_filename);
        in >> n;
        p.reserve(n);
        char s;
        prob_type x;
        for (size_t i = 0; i != n; ++i) {
            in >> s;
            in >> x;
            p.emplace_back(s, x);
        }
        in.close();
    }

    print(p, 0, n - 1);

    return 0;
}
