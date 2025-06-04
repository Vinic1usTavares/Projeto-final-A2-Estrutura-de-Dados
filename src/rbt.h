#ifndef RBT_H
#define RBT_H

#include <string>
#include "tree_utils.h" 

namespace RBT {
    
    //cria uma nova árvore rbt
    BinaryTree* create();

    //insere uma palavra com um id do documento
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    //busca uma palavra na árvore
    SearchResult search(BinaryTree* tree, const std::string& word);

    //libera memória da árvore
    void destroy(BinaryTree* tree);

} //namespace RBT

#endif // RBT_H
