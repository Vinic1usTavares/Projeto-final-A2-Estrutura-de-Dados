#include "tree_utils.h"

void printIndex(BinaryTree* tree);
void printTree(BinaryTree* tree);

Node* createNode(const std::string& word, int docId) {
    Node* node = new Node;
    node->word = word;
    node->documentIds.push_back(docId);
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->height = 1;  // Altura padrão (usado na AVL)
    node->isRed = 0;   // Por padrão, preto. Só será alterado na RBT.
    return node;
}

void destroyNode(Node* node){
    if(node != nullptr){
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
        }
}

void destroyNodeRBT(Node* node, BinaryTree* tree){
    if(node != tree->NIL){
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
        }
}