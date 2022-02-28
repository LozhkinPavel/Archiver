#pragma once

#include <string>

class Trie {
public:
    ~Trie();
    Trie(Trie* left, Trie* right, size_t value);
    Trie(Trie* left, Trie* right, bool terminal, size_t val, uint16_t symbol);
    Trie(size_t val, bool terminal, uint16_t symbol);
    bool GetTerminal();
    bool operator<(const Trie& trie) const;
    uint16_t GetSymbol();
    Trie* GetLeft();
    Trie* GetRight();
    size_t GetValue();
    void Add(uint16_t symbol, size_t code, size_t length);
    Trie* Move(bool side);

private:
    Trie* left0_ = nullptr;
    Trie* right1_ = nullptr;
    size_t value_ = 0;
    bool terminal_ = false;
    uint16_t symbol_ = 0;
};
