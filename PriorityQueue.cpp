#include "PriorityQueue.h"

#include <random>

bool TriePtrCompare(Trie* lhs, Trie* rhs) {
    if (lhs == nullptr) {
        return false;
    }
    if (rhs == nullptr) {
        return true;
    }
    return *lhs < *rhs;
}

PriorityQueue::Node* PriorityQueue::Merge(Node* node1, Node* node2) {
    if (node1 == nullptr) {
        return node2;
    }
    if (node2 == nullptr) {
        return node1;
    }
    int64_t rn = std::mt19937(std::random_device()())();
    if (!TriePtrCompare(node1->val, node2->val)) {
        if (rn % 2 == 0) {
            node1->left = Merge(node1->left, node2);
        } else {
            node1->right = Merge(node1->right, node2);
        }
        return node1;
    } else {
        if (rn % 2 == 0) {
            node2->left = Merge(node2->left, node1);
        } else {
            node2->right = Merge(node2->right, node1);
        }
        return node2;
    }
}

Trie* PriorityQueue::Front() {
    return root->val;
}

void PriorityQueue::Push(Trie* trie) {
    Node* new_node = new Node(trie);
    root = Merge(root, new_node);
    ++size;
}

void PriorityQueue::Pop() {
    if (root == nullptr) {
        return;
    }
    root = Merge(root->left, root->right);
    --size;
}

size_t PriorityQueue::Size() {
    return size;
}
