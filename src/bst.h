#ifndef BST_H
#define BST_H

#include "tree_utils.h"

namespace BST {

    /**
     * Cria a raiz de uma árvore binária.
     * @return O endereço (BinaryTree*) do nó raíz da árvore.
     */
    BinaryTree* create();

    /**
     * Insere na árvore, caso ja não esteja presente, a palvra e o Id do documento ao qual ela pertence.
     * @param tree Endereço da árvore
     * @param word Palavra a ser inserida
     * @param documentID ID do documento
     * @return InsertResult contendo: o número (int) de comparações realizadas e o tempo (double) de execução da função.
     */
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    /**
     * Pesquisa uma palavra na árvore.
     * @param tree Endereço da árvore
     * @param word Palavra a ser pesquisada
     * @return SearchResult contendo: found = 1 caso a palvra for achada ou 0 caso contrário, um vector<int> dos Ids dos documentos em que a palvra esta presente, o tempo (double) de execução da função e o número (int) de comparações realizadas.
     */
    SearchResult search(BinaryTree* tree, const std::string& word);

    /**
     * Destroi recursivamente toda a árvore e seus nós.
     * @param tree Endereço da árvore
     * */
    void destroy(BinaryTree* tree);
}

#endif
