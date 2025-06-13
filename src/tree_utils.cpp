#include "tree_utils.h"
#include <iostream>

// Função auxiliar recursiva para imprimir as palavras e seus IDs de documentos em ordem
void printIndexAux(Node* node, int& count, int max) {
    if (node != nullptr && count < max) {
        // Percorre a subárvore esquerda
        printIndexAux(node->left, count, max);

        // Imprime a palavra e os documentos associados
        count++;
        std::cout << count << ". " << node->word << ": ";

        for (size_t i = 0; i < node->documentIds.size(); ++i) {
            std::cout << node->documentIds[i];
            if (i < node->documentIds.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';

        // Percorre a subárvore direita
        printIndexAux(node->right, count, max);
    }
}

// Função que inicia a impressão do índice da árvore (limite de 50 palavras)
void printIndex(BinaryTree* tree) {
    int count = 0;
    printIndexAux(tree->root, count, 50);
}

// Cria e inicializa um novo nó com valores padrão
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

// Libera recursivamente a memória de todos os nós da árvore
void destroyNode(Node* node) {
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}

// Função auxiliar recursiva para impressão visual da estrutura da árvore
void printTreeNode(Node* node, std::string prefix, bool isLeft) {
    if (node == nullptr) return;

    std::cout << prefix;
    std::cout << (isLeft ? u8"|-- " : u8"'-- ");
    std::cout << node->word << std::endl;

    std::string childPrefix = prefix + (isLeft ? u8"|   " : u8"    ");

    printTreeNode(node->left, childPrefix, true);
    printTreeNode(node->right, childPrefix, false);
}

// Inicia a impressão visual da árvore a partir da raiz
void printTree(BinaryTree* tree) {
    if (tree == nullptr) return; // Verifica se a árvore não é nula

    std::cout << tree->root->word << std::endl;
    printTreeNode(tree->root->left, "", true);
    printTreeNode(tree->root->right, "", false);
}

int GetHeight(Node* root){
    if (root == nullptr){
    return -1; 
    }
    int LeftHeight = GetHeight(root->left);
    int RightHeight = GetHeight(root->right);

    return 1 + std::max(LeftHeight, RightHeight);
}
