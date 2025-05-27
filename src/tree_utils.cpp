#include "tree_utils.h"

void printIndexAux(Node* node, int& count, int max = 50) {
    if (node != nullptr && count < max) {
        count++;
        std::cout << count << ". " << node->word << ": ";

        // Imprime os elementos separados por vírgula, sem vírgula final
        for (size_t i = 0; i < node->documentIds.size(); ++i) {
            std::cout << node->documentIds[i];
            if (i != node->documentIds.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';

        // Ordem lexicográfica (esquerda -> raiz -> direita)
        printIndexAux(node->left, count);
        printIndexAux(node->right, count);
    }
}

void printIndex(BinaryTree* tree) {
    Node* node = tree->root;
    int count = 0;
    printIndexAux(node, count);
}


void printTree(BinaryTree* tree);

Node* createNode() {
    Node* node = new Node;
    node->word = "";
    node->documentIds = {};
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