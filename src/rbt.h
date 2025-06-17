#ifndef RBT_H
#define RBT_H

#include <string>
#include "tree_utils.h" 

namespace RBT {
    
/**
 * @brief Cria e inicializa uma nova Red-Black Tree vazia.
 * 
 * @details Aloca a estrutura da árvore e configura o nó sentinela NIL 
 * (que é sempre preto e compartilhado entre todas as RBTs).
 * 
 * @return BinaryTree* Ponteiro para a árvore alocada. O caller é responsável
 *         por liberar a memória usando RBT::destroy().
 */
BinaryTree* create();

/**
 * @brief Insere uma palavra na árvore associada a um documento.
 * 
 * @param tree Árvore onde a inserção será realizada. Não pode ser nullptr.
 * @param word Palavra a ser inserida. Caso já exista, apenas adiciona o documentId.
 * @param documentId ID do documento relacionado à palavra. Evite valores negativos.
 * 
 * @return InsertResult Estrutura contendo:
 *         - comparisons: Número de comparações realizadas durante a inserção
 *         - time: Tempo de execução em milissegundos
 *         - rotationsCount: Número de rotações para balanceamento (opcional)
 * 
 * @note Complexidade: O(log n) no caso médio e pior caso.
 * @warning Não thread-safe. Para concorrência, gere sincronização externa.
 */
InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

/**
 * @brief Libera completamente a memória utilizada pela árvore.
 * 
 * @param tree Árvore a ser destruída. Após esta chamada, o ponteiro se torna inválido.
 *             Seguro para nullptr (opera como no-op).
 * 
 * @details Percorre a árvore recursivamente, deletando todos os nós
 *          e finalmente a estrutura BinaryTree.
 * 
 * @example
 *    BinaryTree* tree = RBT::create();
 *    // ... operações ...
 *    RBT::destroy(tree); // tree não deve ser usado após isso
 */
void destroy(BinaryTree* tree);

} //namespace RBT

#endif // RBT_H
