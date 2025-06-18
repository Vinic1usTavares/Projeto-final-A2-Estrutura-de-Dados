#ifndef RBT_H
#define RBT_H

#include <string>
#include "tree_utils.h"

namespace RBT {

    /**
     * @brief Cria e inicializa uma nova árvore Rubro-Negra.
     * 
     * @return Ponteiro para a estrutura BinaryTree recém-criada.
     */
    BinaryTree* create();

    /**
     * @brief Insere uma palavra na árvore associada a um ID de documento.
     * 
     * Se a palavra já existir, o ID do documento é adicionado à lista correspondente.
     * Caso contrário, a palavra é inserida com o ID do documento como primeiro registro.
     * 
     * @param tree Ponteiro para a árvore Rubro-Negra.
     * @param word Palavra a ser inserida.
     * @param documentId Identificador do documento onde a palavra foi encontrada.
     * @return Estrutura InsertResult com informações sobre a operação.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Realiza a busca por uma palavra na árvore.
     * 
     * @param tree Ponteiro para a árvore Rubro-Negra.
     * @param word Palavra a ser buscada.
     * @return Estrutura SearchResult contendo os dados encontrados ou informação de ausência.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera toda a memória alocada pela árvore.
     * 
     * Remove todos os nós e limpa os dados associados à árvore.
     * 
     * @param tree Ponteiro para a árvore a ser destruída.
     */
    void destroy(BinaryTree* tree);

} // namespace RBT

#endif // RBT_H

