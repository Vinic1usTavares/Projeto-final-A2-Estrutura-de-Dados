#include "tree_utils.h"
#include <iostream>


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

    Node* root = tree->root;
    std::cout << tree->root->word << std::endl;


    printTreeNode(tree->root->left, "", true);
    printTreeNode(tree->root->right, "", false);

}


