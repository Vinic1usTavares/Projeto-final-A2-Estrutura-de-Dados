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
    // - tree: ponteiro para a árvore AVL a ser destruída
    void destroy(BinaryTree* tree);
}

#endif
