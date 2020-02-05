#pragma once

#include <iostream>
#include <vector>

#include "util.hpp"

namespace huffman {

template <typename Symbol, typename Weight>
struct node {
    weighted_symbol<Symbol, Weight> symbol;
    node<Symbol, Weight>* left;
    node<Symbol, Weight>* right;
};

template <typename Symbol, typename Weight>
static node<Symbol, Weight>* make_leaf(weighted_symbol<Symbol, Weight> ws) {
    node<Symbol, Weight>* leaf = new node<Symbol, Weight>();
    leaf->symbol.s = ws.s;
    leaf->symbol.w = ws.w;
    leaf->left = nullptr;
    leaf->right = nullptr;
    return leaf;
}

template <typename Node>
static Node* make_internal(Node* left, Node* right) {
    Node* n = new Node();
    n->symbol.w = left->symbol.w + right->symbol.w;
    n->left = left;
    n->right = right;
    return n;
}

template <typename Node>
bool is_leaf(Node const* n) {
    return n->left == nullptr and n->right == nullptr;
}

template <typename Symbol, typename Weight>
node<Symbol, Weight>* build_tree(
    std::vector<weighted_symbol<Symbol, Weight>>& p, bool verbose = false) {
    std::sort(p.begin(), p.end(),
              [](auto const& x, auto const& y) { return x.w < y.w; });

    typedef node<Symbol, Weight>* node_ptr;

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
            if (p[leaf].w <= internal_nodes[internal]->symbol.w) {
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
            std::cout << "created internal node with weight " << l->symbol.w
                      << " + " << r->symbol.w << " = " << n->symbol.w
                      << std::endl;
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
        return c.length() * n->symbol.w;
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
