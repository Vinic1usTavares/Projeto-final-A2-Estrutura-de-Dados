#ifndef AVL_H
#define AVL_H

#include "tree_utils.h"
#include <string>

// Namespace que encapsula todas as funcionalidades relacionadas 
// à árvore AVL (Adelson-Velsky and Landis).
namespace AVL {

    // Cria e inicializa uma nova árvore AVL.
    // Retorna um ponteiro para a árvore binária com raiz nula.
    BinaryTree* create();

    // Insere uma palavra na árvore AVL associada a um determinado documento.
    // Parâmetros:
    // - tree: ponteiro para a árvore AVL
    // - word: palavra a ser inserida
    // - documentId: ID do documento onde a palavra foi encontrada
    // Retorna um InsertResult contendo informações sobre a operação (comparacoes e tempo).
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    // Busca uma palavra na árvore AVL.
    // Parâmetros:
    // - tree: ponteiro para a árvore AVL
    // - word: palavra a ser buscada
    // Retorna um SearchResult com os documentos encontrados e estatísticas da busca.
    SearchResult search(BinaryTree* tree, const std::string& word);

    // Libera toda a memória alocada pela árvore AVL.
    // Parâmetro:
    // - tree: ponteiro para a árvore AVL a ser destruída.
    void destroy(BinaryTree* tree);

    // Retorna a altura de um nó da árvore AVL.
    // Parâmetro:
    // - node: ponteiro para o nó cuja altura será retornada.
    // Retorna a altura do nó (0 se for nulo).
    int height(Node* node);

    // Retorna o maior entre dois valores inteiros.
    // Parâmetros:
    // - a: primeiro valor inteiro.
    // - b: segundo valor inteiro.
    // Retorna o maior valor entre a e b.
    int max(int a, int b);

    // Calcula o fator de balanceamento de um nó da árvore AVL.
    // Parâmetro:
    // - node: ponteiro para o nó cujo fator de balanceamento será calculado.
    // Retorna a diferença entre as alturas das subárvores esquerda e direita.
    int balanceFactor(Node* node);

    // Executa uma rotação simples para a direita.
    // Parâmetro:
    // - y: ponteiro para o nó desbalanceado.
    // Retorna o novo nó raiz da subárvore após a rotação.
    Node* rotateRight(Node* y);

    // Executa uma rotação simples para a esquerda.
    // Parâmetro:
    // - x: ponteiro para o nó desbalanceado.
    // Retorna o novo nó raiz da subárvore após a rotação.
    Node* rotateLeft(Node* x);

    // Função auxiliar recursiva para inserir uma palavra na árvore AVL e realizar balanceamento.
    // Parâmetros:
    // - node: ponteiro para o nó atual da árvore.
    // - word: palavra a ser inserida.
    // - docId: ID do documento onde a palavra foi encontrada.
    // - comparisons: referência para contador de comparações realizadas durante a inserção.
    // Retorna o ponteiro para o nó atualizado após inserção e balanceamento.
    Node* insertAux(Node* node, const std::string& word, int docId, int& comparisons);
}

#endif
