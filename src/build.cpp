#include <algorithm>
#include <fstream>
#include <iostream>

#include "../include/shannon_fano.hpp"
#include "../include/huffman.hpp"

int main(int argc, char** argv) {
    int mandatory = 1 + 2;
    if (argc < mandatory) {
        std::cerr << argv[0] << "type input_filename --verbose" << std::endl;
        return 1;
    }

    std::string type = argv[1];
    char const* input_filename = argv[2];
    bool verbose = false;
    if (argc > mandatory and std::string(argv[mandatory]) == "--verbose") {
        verbose = true;
    }

    std::vector<weighted_symbol<char, float>> p;
    size_t n = 0;
    {
        std::ifstream in(input_filename);
        in >> n;
        p.reserve(n);
        char s;
        float x;
        for (size_t i = 0; i != n; ++i) {
            in >> s;
            in >> x;
            p.emplace_back(s, x);
        }
        in.close();
    }

    double L = 0.0;
    if (type == "shannon_fano") {
        L = shannon_fano::print(p, verbose);
    } else if (type == "huffman") {
        auto root = huffman::build_tree(p, verbose);
        codeword c;
        L = huffman::print_tree(root, c, verbose);
        huffman::free_tree(root);
    } else {
        std::cerr << "unknown type '" << type << "'" << std::endl;
        return 1;
    }

    std::cout << "average codeword length: " << L << " bits" << std::endl;

    return 0;
}
