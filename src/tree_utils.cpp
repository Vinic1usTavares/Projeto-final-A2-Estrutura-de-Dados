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


// Função auxiliar para imprimir cada nó recursivamente
void printTreeNode(Node* node, std::string prefix, bool isLeft) {
    if (node == nullptr) return;

    std::cout << prefix;
    std::cout << (isLeft ? u8"|-- " : u8"'-- ");

    std::cout << node->word << std::endl;

    std::string childPrefix = prefix + (isLeft ? u8"|   " : u8"    ");

    printTreeNode(node->left, childPrefix, true);
    printTreeNode(node->right, childPrefix, false);
}

void printTree(BinaryTree* tree) {
    if (tree == nullptr) return; //checks if it is not a null pointer

    std::cout << tree->root->word << std::endl;


    printTreeNode(tree->root->left, "", true);
    printTreeNode(tree->root->right, "", false);

}

