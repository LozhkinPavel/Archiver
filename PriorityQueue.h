#pragma once

#include "Trie.h"
#include <queue>

class PriorityQueue {
public:
    size_t Size();
    Trie* Front();
    void Push(Trie* trie);
    void Pop();

private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Trie* val;
        ~Node() {
            delete left;
            delete right;
        }
        Node(Trie* value) : val(value){};
    };
    Node* root = nullptr;
    Node* Merge(Node* node1, Node* node2);
    size_t size = 0;
};
