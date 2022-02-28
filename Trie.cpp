#include "Trie.h"
#include <iostream>

Trie::~Trie() {
    delete left0_;
    delete right1_;
}

Trie::Trie(Trie *left, Trie *right, size_t value) : left0_(left), right1_(right), value_(value) {
}

Trie::Trie(Trie *left, Trie *right, bool terminal, size_t val, uint16_t symbol)
    : left0_(left), right1_(right), value_(val), terminal_(terminal), symbol_(symbol) {
}

Trie::Trie(size_t val, bool terminal, uint16_t symbol) : value_(val), terminal_(terminal), symbol_(symbol) {
}

size_t Trie::GetValue() {
    return value_;
}

bool Trie::GetTerminal() {
    return terminal_;
}

uint16_t Trie::GetSymbol() {
    return symbol_;
}

Trie *Trie::GetLeft() {
    return left0_;
}

Trie *Trie::GetRight() {
    return right1_;
}

bool Trie::operator<(const Trie &trie) const {
    return value_ > trie.value_;
}

void Trie::Add(uint16_t symbol, size_t code, size_t length) {
    auto current_vertex = this;
    for (size_t i = 0; i < length; ++i) {
        bool current_bit = (code >> (length - 1 - i)) & 1;
        if (current_bit == true) {
            if (current_vertex->right1_ == nullptr) {
                current_vertex->right1_ = new Trie(nullptr, nullptr, 0);
            }
            current_vertex = current_vertex->right1_;
        } else {
            if (current_vertex->left0_ == nullptr) {
                current_vertex->left0_ = new Trie(nullptr, nullptr, 0);
            }
            current_vertex = current_vertex->left0_;
        }
    }
    current_vertex->terminal_ = true;
    current_vertex->symbol_ = symbol;
}

Trie *Trie::Move(bool side) {
    if (side) {
        return this->right1_;
    }
    return this->left0_;
}
