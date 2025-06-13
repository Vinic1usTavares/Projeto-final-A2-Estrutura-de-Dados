#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

// Estrutura que representa um nó de uma árvore binária
struct Node {
    std::string word;               // Palavra armazenada no nó
    std::vector<int> documentIds;   // IDs dos documentos onde a palavra aparece
    Node* parent;                   // Ponteiro para o nó pai
    Node* left;                     // Ponteiro para o filho esquerdo
    Node* right;                    // Ponteiro para o filho direito
    int height;                     // Altura do nó (usado em árvores AVL)
    int isRed;                      // Indica se o nó é vermelho (usado em árvores rubro-negras)
};

// Estrutura que representa uma árvore binária
struct BinaryTree {
    Node* root;  // Raiz da árvore
    Node* NIL;   // Nó sentinela (usado em RBT, pode ser ignorado para AVL)
};

// Resultado da inserção de uma palavra na árvore
struct InsertResult {
    int numComparisons;    // Número de comparações realizadas
    double executionTime;  // Tempo gasto na inserção (em milissegundos)
};

// Resultado da busca por uma palavra na árvore
struct SearchResult {
    int found;                      // Indica se a palavra foi encontrada (1) ou não (0)
    std::vector<int> documentIds;  // Lista de IDs dos documentos encontrados
    double executionTime;          // Tempo da busca (em milissegundos)
    int numComparisons;            // Número de comparações realizadas durante a busca
};

// Imprime as palavras e os documentos associados em ordem, até um limite de palavras
void printIndexAux(Node* node, int& count, int max);

// Função de interface que imprime até 50 palavras indexadas
void printIndex(BinaryTree* tree);

// Imprime graficamente a estrutura da árvore, com ramos visuais
void printTree(BinaryTree* tree);

// Cria um novo nó da árvore, inicializando seus campos
Node* createNode();

// Destroi recursivamente todos os nós da árvore
void destroyNode(Node* node);

// Encontra a altura de uma árvore
int GetHeight(Node* root);



#endif
