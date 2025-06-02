/**
 * @file tree_utils.cpp
 * @brief Implementação de utilitários para manipulação de árvores binárias
 * 
 * Contém funções auxiliares para:
 * - Impressão do índice
 * - Criação e destruição de nós
 * - Operações básicas de árvores
 */

#include "tree_utils.h"
#include <iostream>

/**
 * @brief Função auxiliar recursiva para impressão do índice
 * @param node Nó atual sendo processado
 * @param count Referência ao contador de itens impressos (in-out)
 * @param max Número máximo de itens a exibir
 * 
 * @note Realiza travessia em-ordem (esquerda-raiz-direita)
 * @warning O parâmetro count é modificado durante a execução
 */
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

/**
 * @brief Imprime uma amostra do índice contido na árvore
 * @param tree Ponteiro para a árvore contendo o índice
 * @param max_items Número máximo de itens a exibir (padrão=50)
 * 
 * @example
 * 1. algorithm: 10, 25, 42
 * 2. data: 3, 18
 * 3. structure: 7
 */
void printIndex(BinaryTree* tree, int max_items = 50) {
    int count = 0;
    printIndexAux(tree->root, count, max_items);
}

/**
 * @brief Cria um novo nó de árvore com valores padrão
 * @return Ponteiro para o nó alocado
 * 
 * @details Inicializa:
 * - word: string vazia
 * - documentIds: vetor vazio
 * - ponteiros (left, right, parent): nullptr
 * - height: 1
 * - isRed: 0 (para Red-Black Trees)
 */
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

/**
 * @brief Destrói recursivamente uma subárvore
 * @param node Raiz da subárvore a ser destruída
 * 
 * @note Realiza travessia pós-ordem (esquerda-direita-raiz)
 * @warning Libera toda a memória da subárvore
 */
void destroyNode(Node* node) {
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}

/**
 * @brief Destrói recursivamente uma subárvore Red-Black
 * @param node Raiz da subárvore
 * @param tree Ponteiro para a árvore (contém referência ao NIL)
 * 
 * @note Versão especializada para Red-Black Trees
 * @see destroyNode()
 */
void destroyNodeRBT(Node* node, BinaryTree* tree) {
    if (node != tree->NIL) {
        destroyNodeRBT(node->left, tree);
        destroyNodeRBT(node->right, tree);
        delete node;
    }
}