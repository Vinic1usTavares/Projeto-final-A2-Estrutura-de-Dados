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
/**
 * @brief Verifica se a propriedade de cores da Red-Black Tree está mantida.
 * 
 * @param node Nó atual da árvore sendo verificado.
 * @param NIL Ponteiro para o nó sentinela NIL da árvore.
 * 
 * @return true se nenhum nó vermelho possui filho vermelho (propriedade 4 da RBT),
 *         false caso contrário.
 * 
 * @details Esta função percorre a árvore recursivamente para garantir que não exista
 *          nenhum nó vermelho com filho vermelho, condição fundamental para o balanceamento
 *          das Red-Black Trees.
 */
bool checkRedProperty(Node* node, Node* NIL);


/**
 * @brief Calcula a altura negra da árvore a partir do nó dado.
 * 
 * @param node Nó raiz da subárvore a ser verificada.
 * @param NIL Ponteiro para o nó sentinela NIL da árvore.
 * 
 * @return Número de nós pretos em qualquer caminho da raiz até uma folha NIL.
 *         Retorna 0 se a propriedade de contagem igual de nós pretos não for satisfeita.
 * 
 * @details A altura negra é o número de nós pretos do nó atual até uma folha NIL.
 *          Esta função verifica se todos os caminhos têm a mesma altura negra,
 *          condição necessária para o balanceamento correto da Red-Black Tree.
 */
int blackHeight(Node* node, Node* NIL);

} // namespace RBT

#endif // RBT_H
