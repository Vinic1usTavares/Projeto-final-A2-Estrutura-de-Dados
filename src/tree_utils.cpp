#include "tree_utils.h"
#include <iostream>

void printIndexAux(Node* node, int& count, int max) {
    if (node != nullptr && count < max) {
        printIndexAux(node->left, count, max);
        
        count++;
        std::cout << count << ". " << node->word << ": ";
        
        for (size_t i = 0; i < node->documentIds.size(); ++i) {
            std::cout << node->documentIds[i];
            if (i < node->documentIds.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';
        
        printIndexAux(node->right, count, max);
    }
}

void printIndex(BinaryTree* tree) {
    int count = 0;
    printIndexAux(tree->root, count, 50);
}

Node* createNode() {
    Node* node = new Node;
    node->word = "";
    node->documentIds = {};
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->height = 1;
    node->isRed = 0;
    return node;
}

int main() {
    return 0;
}

