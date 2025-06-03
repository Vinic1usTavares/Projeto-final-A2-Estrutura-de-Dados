/**
 * @file tree_utils.h
 * @brief Definições de estruturas e funções utilitárias para árvores binárias
 * 
 * Contém as estruturas básicas e operações para:
 * - Árvores AVL
 * - Red-Black Trees (RBT)
 * - Operações comuns de manipulação
 */

#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ctime>

/**
 * @struct Node
 * @brief Nó base para árvores binárias
 * 
 * @var word Palavra armazenada no nó
 * @var documentIds Vetor de IDs de documentos que contêm a palavra
 * @var parent Ponteiro para o nó pai
 * @var left Ponteiro para o filho esquerdo
 * @var right Ponteiro para o filho direito
 * @var height Altura do nó (usado em AVL)
 * @var isRed Indicador de cor (0=preto, 1=vermelho - usado em RBT)
 */
struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

/**
 * @struct BinaryTree
 * @brief Estrutura contendo a raiz de uma árvore binária
 * 
 * @var root Ponteiro para o nó raiz
 * @var NIL Ponteiro para o nó sentinela (usado em RBT)
 */
struct BinaryTree {
    Node* root;
    Node* NIL; // usado na RBT (opcional)
};

/**
 * @struct InsertResult
 * @brief Resultado de operações de inserção
 * 
 * @var numComparisons Número de comparações realizadas
 * @var executionTime Tempo de execução em milissegundos
 */
struct InsertResult {
    int numComparisons;
    double executionTime;
};

/**
 * @struct SearchResult
 * @brief Resultado de operações de busca
 * 
 * @var found Indicador de sucesso (1=encontrado, 0=não encontrado)
 * @var documentIds IDs de documentos onde a palavra foi encontrada
 * @var executionTime Tempo de execução em milissegundos
 * @var numComparisons Número de comparações realizadas
 */
struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};

/**
 * @brief Função auxiliar para impressão recursiva do índice
 * @param node Nó atual sendo processado
 * @param count Contador de itens impressos (passado por referência)
 * @param max Número máximo de itens a exibir
 */
void printIndexAux(Node* node, int& count, int max);

/**
 * @brief Imprime uma amostra do índice contido na árvore
 * @param tree Árvore contendo o índice a ser impresso
 * @note Exibe no máximo 50 itens por padrão
 */
void printIndex(BinaryTree* tree);

/**
 * @brief Imprime a estrutura da árvore (fins de depuração)
 * @param tree Árvore a ser exibida
 * @warning Formato de saída não padronizado - uso para debug apenas
 */
void printTree(BinaryTree* tree);

/**
 * @brief Cria um novo nó inicializado com valores padrão
 * @return Ponteiro para o nó alocado
 * @see Node
 */
Node* createNode();

/**
 * @brief Destrói recursivamente uma subárvore
 * @param node Raiz da subárvore a ser destruída
 * @note Libera toda a memória associada aos nós
 */
void destroyNode(Node* node);

/**
 * @brief Destrói recursivamente uma subárvore Red-Black
 * @param node Raiz da subárvore
 * @param tree Árvore contendo o nó NIL de referência
 * @note Versão especializada para Red-Black Trees
 */
void destroyNodeRBT(Node* node, BinaryTree* tree);

#endif // TREE_UTILS_H