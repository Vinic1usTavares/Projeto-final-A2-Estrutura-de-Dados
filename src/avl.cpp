#include "avl.h"
#include "tree_utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

namespace AVL {

BinaryTree* create() {
    BinaryTree* tree = new BinaryTree;
    tree->root = nullptr;
    tree->NIL = nullptr;
    return tree;
}

int height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int balanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insertAux(Node* node, const std::string& word, int docId, int& comparisons) {
    if (node == nullptr) {
        Node* newNode = createNode();
        newNode->word = word;
        newNode->documentIds.push_back(docId);
        return newNode;
    }

    comparisons++;
    if (word < node->word) {
        node->left = insertAux(node->left, word, docId, comparisons);
    } else if (word > node->word) {
        node->right = insertAux(node->right, word, docId, comparisons);
    } else {
        if (node->documentIds.empty() || node->documentIds.back() != docId) {
            node->documentIds.push_back(docId);
        }
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    // Casos de rotação
    if (balance > 1 && word < node->left->word) {
        return rotateRight(node);
    }
    if (balance < -1 && word > node->right->word) {
        return rotateLeft(node);
    }
    if (balance > 1 && word > node->left->word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && word < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;

    tree->root = insertAux(tree->root, word, documentId, comparisons);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {comparisons, duration.count()};
}

SearchResult search(BinaryTree* tree, const std::string& word) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;
    Node* node = tree->root;

    while (node != nullptr) {
        comparisons++;
        if (word == node->word) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            return {1, node->documentIds, duration.count(), comparisons};
        }

        if (word < node->word) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {0, {}, duration.count(), comparisons};
}

void destroy(BinaryTree* tree) {
    if (tree != nullptr) {
        destroyNode(tree->root);
        delete tree;
    }
}

} // namespace AVL