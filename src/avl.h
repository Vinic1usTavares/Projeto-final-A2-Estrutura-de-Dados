/**
 * @file avl.h
 * @brief Definição da estrutura de dados AVL Tree para indexação de palavras.
 * 
 * Este arquivo contém as declarações das operações básicas de uma Árvore AVL
 * utilizada para armazenar palavras e seus documentos associados.
 */

#ifndef AVL_H
#define AVL_H

#include "tree_utils.h"
#include <string>

/**
 * @namespace AVL
 * @brief Namespace que encapsula as operações da Árvore AVL.
 */
namespace AVL {
    /**
     * @brief Cria uma nova árvore AVL vazia.
     * @return Ponteiro para a raiz da árvore criada (inicialmente nulo).
     */
    BinaryTree* create();

    /**
     * @brief Insere uma palavra na árvore AVL com seu ID de documento associado.
     * @param tree Ponteiro para a árvore onde a inserção será realizada.
     * @param word Palavra a ser inserida.
     * @param documentId ID do documento onde a palavra aparece.
     * @return InsertResult Struct contendo:
     *         - `status`: booleano indicando sucesso (true) ou falha (false).
     *         - `node`: ponteiro para o nó inserido/modificado.
     * @note A árvore é automaticamente balanceada após a inserção.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Busca uma palavra na árvore AVL.
     * @param tree Ponteiro para a árvore onde a busca será realizada.
     * @param word Palavra a ser buscada.
     * @return SearchResult Struct contendo:
     *         - `found`: booleano indicando se a palavra existe.
     *         - `node`: ponteiro para o nó encontrado (nullptr se não existir).
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera toda a memória alocada pela árvore AVL.
     * @param tree Ponteiro para a árvore a ser destruída.
     * @note Após a chamada, o ponteiro `tree` torna-se inválido.
     */
    void destroy(BinaryTree* tree);
}

#endif