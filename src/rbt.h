#ifndef RBT_H
#define RBT_H

#include <string>
#include "tree_utils.h"  // inclui a definição de BinaryTree e Node

namespace RBT {

    // cria uma nova árvore rubro-negra
    BinaryTree* create();

    // insere uma palavra com um ID de documento
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    // busca uma palavra na árvore
    SearchResult search(BinaryTree* tree, const std::string& word);

    // libera memória da árvore
    void deleteTree(BinaryTree* tree);

} // namespace RBT

#endif // RBT_H
