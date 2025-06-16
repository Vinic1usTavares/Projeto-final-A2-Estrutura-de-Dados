#include "avl.h"
#include "tree_utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

namespace AVL {

// Cria uma nova árvore AVL vazia
BinaryTree* create() {
    BinaryTree* tree = new BinaryTree;
    tree->root = nullptr;
    tree->NIL = nullptr;
    return tree;
}

// Retorna a altura de um nó (0 se for nulo)
int height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

// Retorna o maior entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calcula o fator de balanceamento de um nó (altura da subárvore esquerda - direita)
int balanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Rotação simples para a direita
Node* rotateRight(Node* y, int& rotationsCount) {
    rotationsCount ++;
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação simples para a esquerda
Node* rotateLeft(Node* x, int& rotationsCount) {
    rotationsCount ++;
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Função recursiva auxiliar para inserção e balanceamento
Node* insertAux(Node* node, const std::string& word, int docId, int& comparisons, int& rotationsCount) {
    if (node == nullptr) {
        Node* newNode = createNode();
        newNode->word = word;
        newNode->documentIds.push_back(docId);
        return newNode;
    }

    comparisons++;
    if (word < node->word) {
        node->left = insertAux(node->left, word, docId, comparisons, rotationsCount);
    } else if (word > node->word) {
        node->right = insertAux(node->right, word, docId, comparisons, rotationsCount);
    } else {
        // Palavra já está na árvore: adiciona ID do documento se ainda não estiver presente
        if (node->documentIds.empty() || node->documentIds.back() != docId) {
            node->documentIds.push_back(docId);
        }
        return node;
    }

    // Atualiza altura do nó atual
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    // Casos de desbalanceamento e rotação
    if (balance > 1 && word < node->left->word) {
        return rotateRight(node, rotationsCount); // Caso esquerda-esquerda
    }
    if (balance < -1 && word > node->right->word) {
        return rotateLeft(node, rotationsCount); // Caso direita-direita
    }
    if (balance > 1 && word > node->left->word) {
        node->left = rotateLeft(node->left, rotationsCount); // Caso esquerda-direita
        return rotateRight(node, rotationsCount);
    }
    if (balance < -1 && word < node->right->word) {
        node->right = rotateRight(node->right, rotationsCount); // Caso direita-esquerda
        return rotateLeft(node, rotationsCount);
    }

    return node; // Retorna nó já balanceado
}

// Insere uma palavra na árvore AVL e retorna estatísticas da inserção
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;
    int rotationsCount = 0;

    tree->root = insertAux(tree->root, word, documentId, comparisons, rotationsCount);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {comparisons, duration.count(), rotationsCount};
}

// Busca uma palavra na árvore AVL e retorna informações da busca
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

// Libera a memória ocupada pela árvore
void destroy(BinaryTree* tree) {
    if (tree != nullptr) {
        destroyNode(tree->root);
        delete tree;
    }
}

} // namespace AVL