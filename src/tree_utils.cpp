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



//teste das funções
Node* criarNode(const std::string& palavra, std::vector<int> ids = {}) {
    Node* node = new Node;
    node->word = palavra;
    node->documentIds = ids;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;
    node->isRed = 0;
    return node;
}

int main() {
    return 0;
}

