#pragma once

#include <iostream>
#include <vector>

#include "util.hpp"

namespace huffman {

template <typename Symbol>
struct node {
    symbol_probability<Symbol> symbol;
    node<Symbol>* left;
    node<Symbol>* right;
};

template <typename Symbol>
static node<Symbol>* make_leaf(symbol_probability<Symbol> const& sf) {
    node<Symbol>* n = new node<Symbol>();
    n->symbol.s = sf.s;
    n->symbol.p = sf.p;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

template <typename Symbol>
static node<Symbol>* make_internal(node<Symbol>* left, node<Symbol>* right) {
    node<Symbol>* n = new node<Symbol>();
    n->symbol.p = left->symbol.p + right->symbol.p;
    n->left = left;
    n->right = right;
    return n;
}

template <typename Symbol>
bool is_leaf(node<Symbol> const* n) {
    return n->left == nullptr and n->right == nullptr;
}

template <typename Symbol>
node<Symbol>* build_tree(std::vector<symbol_probability<Symbol>>& p,
                         bool verbose = false) {
    std::sort(p.begin(), p.end(),
              [](auto const& x, auto const& y) { return x.p < y.p; });

    typedef node<Symbol>* node_ptr;

    size_t leaf = 0;
    size_t internal = 0;
    std::vector<node_ptr> internal_nodes;
    internal_nodes.reserve(p.size() - 1);

    auto select_next = [&]() {
        node_ptr n = nullptr;
        if (leaf == p.size()) {
            n = internal_nodes[internal++];
        } else if (internal == internal_nodes.size()) {
            n = make_leaf(p[leaf++]);
        } else {
            if (p[leaf].p <= internal_nodes[internal]->symbol.p) {
                n = make_leaf(p[leaf++]);
            } else {
                n = internal_nodes[internal++];
            }
        }
        return n;
    };

    while (internal_nodes.size() != p.size() - 1) {
        node_ptr l = select_next();
        node_ptr r = select_next();
        node_ptr n = make_internal(l, r);
        if (verbose) {
            std::cout << "created internal node with probability "
                      << l->symbol.p << " + " << r->symbol.p << " = "
                      << n->symbol.p << std::endl;
        }
        internal_nodes.push_back(n);
    }

    node_ptr root = internal_nodes.back();
    return root;
}

template <typename Node>
double print_tree(Node const* n, codeword c, bool verbose) {
    if (is_leaf(n)) {
        std::cout << "C(" << n->symbol.s << ") = " << c << std::endl;
        return c.length() * n->symbol.p;
    }
    return print_tree(n->left, c + 0, verbose) +
           print_tree(n->right, c + 1, verbose);
}

template <typename Node>
void free_tree(Node* n) {
    if (is_leaf(n)) {
        free(n);
        return;
    }
    free_tree(n->left);
    free_tree(n->right);
}

}  // namespace huffman
