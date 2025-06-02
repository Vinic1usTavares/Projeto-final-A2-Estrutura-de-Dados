/**
 * @file avl.cpp
 * @brief Implementação de uma árvore AVL para indexação de documentos
 * 
 * Esta implementação fornece operações básicas de criação, inserção, busca e destruição
 * de uma árvore AVL balanceada, com medição de tempo e contagem de comparações.
 */

#include "avl.h"
#include "tree_utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

namespace AVL {

/**
 * @brief Cria e inicializa uma nova árvore AVL vazia
 * @return Ponteiro para a árvore criada
 * @complexidade O(1)
 */
BinaryTree* create() {
    BinaryTree* tree = new BinaryTree;
    tree->root = nullptr;
    tree->NIL = nullptr;
    return tree;
}

/**
 * @brief Calcula a altura de um nó
 * @param node Nó da árvore
 * @return Altura do nó (0 para nó nulo)
 * @complexidade O(1)
 */
int height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

/**
 * @brief Retorna o maior entre dois inteiros
 * @param a Primeiro valor
 * @param b Segundo valor
 * @return O maior valor entre a e b
 * @complexidade O(1)
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * @brief Calcula o fator de balanceamento de um nó
 * @param node Nó da árvore
 * @return Fator de balanceamento (diferença de altura das subárvores)
 * @complexidade O(1)
 */
int balanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

/**
 * @brief Realiza rotação simples à direita
 * @param y Nó desbalanceado
 * @return Nova raiz da subárvore
 * @complexidade O(1)
 * @example
 *     y       x
 *    / \     / \
 *   x   C → A   y
 *  / \         / \
 * A   B       B   C
 */
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

/**
 * @brief Realiza rotação simples à esquerda
 * @param x Nó desbalanceado
 * @return Nova raiz da subárvore
 * @complexidade O(1)
 * @example
 *   x         y
 *  / \       / \
 * A   y →   x   C
 *    / \   / \
 *   B   C A   B
 */
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

/**
 * @brief Função auxiliar recursiva para inserção na árvore AVL
 * @param node Nó atual sendo analisado
 * @param word Palavra a ser inserida
 * @param docId ID do documento contendo a palavra
 * @param comparisons Contador de comparações (incrementado por referência)
 * @return Novo nó raiz da subárvore após inserção e balanceamento
 * @complexidade O(log n)
 */
Node* insertAux(Node* node, const std::string& word, int docId, int& comparisons) {
    // Caso base: chegou a posição de inserção
    if (node == nullptr) {
        Node* newNode = createNode();
        newNode->word = word;
        newNode->documentIds.push_back(docId);
        return newNode;
    }

    comparisons++;
    // Inserção na subárvore esquerda
    if (word < node->word) {
        node->left = insertAux(node->left, word, docId, comparisons);
    } 
    // Inserção na subárvore direita
    else if (word > node->word) {
        node->right = insertAux(node->right, word, docId, comparisons);
    } 
    // Palavra já existe - adiciona documento se necessário
    else {
        if (node->documentIds.empty() || node->documentIds.back() != docId) {
            node->documentIds.push_back(docId);
        }
        return node;
    }

    // Atualiza altura do nó atual
    node->height = 1 + max(height(node->left), height(node->right));

    // Verifica balanceamento
    int balance = balanceFactor(node);

    // Casos de desbalanceamento:

    // Rotação simples à direita
    if (balance > 1 && word < node->left->word) {
        return rotateRight(node);
    }
    
    // Rotação simples à esquerda
    if (balance < -1 && word > node->right->word) {
        return rotateLeft(node);
    }
    
    // Rotação dupla esquerda-direita
    if (balance > 1 && word > node->left->word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Rotação dupla direita-esquerda
    if (balance < -1 && word < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

/**
 * @brief Insere uma nova palavra na árvore AVL
 * @param tree Árvore onde será inserida a palavra
 * @param word Palavra a ser inserida
 * @param documentId ID do documento que contém a palavra
 * @return InsertResult com número de comparações e tempo de execução
 * @complexidade O(log n)
 */
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;

    // Chama a função auxiliar de inserção
    tree->root = insertAux(tree->root, word, documentId, comparisons);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {comparisons, duration.count()};
}

/**
 * @brief Busca uma palavra na árvore AVL
 * @param tree Árvore onde será realizada a busca
 * @param word Palavra a ser buscada
 * @return SearchResult com informações da busca
 * @complexidade O(log n)
 */
SearchResult search(BinaryTree* tree, const std::string& word) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;
    Node* node = tree->root;

    // Percorre a árvore procurando a palavra
    while (node != nullptr) {
        comparisons++;
        
        // Palavra encontrada
        if (word == node->word) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            return {1, node->documentIds, duration.count(), comparisons};
        }

        // Continua busca na subárvore esquerda ou direita
        if (word < node->word) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    // Palavra não encontrada
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {0, {}, duration.count(), comparisons};
}

/**
 * @brief Libera toda a memória alocada pela árvore
 * @param tree Árvore a ser destruída
 * @complexidade O(n)
 */
void destroy(BinaryTree* tree) {
    if (tree != nullptr) {
        destroyNode(tree->root);
        delete tree;
    }
}

} // namespace AVL