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
     * Destroi recursivamente toda a árvore e seus nós.
     * @param tree Endereço da árvore
     * */
    void destroy(BinaryTree* tree);
}

#endif
