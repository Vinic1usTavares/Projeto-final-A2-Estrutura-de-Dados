#ifndef RBT_H
#define RBT_H

#include <string>
#include "tree_utils.h" 

namespace RBT {
    
    /**
     * @brief Cria uma nova árvore Rubro-Negra vazia.
     * 
     * Inicializa os ponteiros e a estrutura da árvore, incluindo o nó NIL (folhas nulas),
     * que é compartilhado por todos os nós terminais da árvore.
     * 
     * @return Ponteiro para a nova árvore criada.
     */
    BinaryTree* create();

    /**
     * @brief Insere uma palavra na árvore associada a um ID de documento.
     * 
     * Caso a palavra já exista, apenas adiciona o ID do documento ao vetor, evitando duplicatas consecutivas.
     * Caso não exista, insere a palavra e realiza as rotações e recolorações necessárias para manter
     * as propriedades da árvore Rubro-Negra.
     * 
     * @param tree Ponteiro para a árvore.
     * @param word Palavra a ser inserida.
     * @param documentId ID do documento onde a palavra ocorre.
     * @return Struct InsertResult contendo o número de comparações e o tempo de execução em milissegundos.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * @brief Realiza a busca de uma palavra na árvore.
     * 
     * Se a palavra for encontrada, retorna os IDs dos documentos em que ela ocorre,
     * juntamente com informações de desempenho (tempo e comparações).
     * 
     * @param tree Ponteiro para a árvore.
     * @param word Palavra a ser buscada.
     * @return Struct SearchResult contendo o vetor de IDs, tempo de execução, número de comparações e se encontrou ou não.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * @brief Libera toda a memória alocada pela árvore.
     * 
     * Destrói todos os nós da árvore, incluindo o nó raiz e libera o ponteiro da estrutura principal.
     * 
     * @param tree Ponteiro para a árvore que será destruída.
     */
    void destroy(BinaryTree* tree);

} // namespace RBT

#endif // RBT_H
