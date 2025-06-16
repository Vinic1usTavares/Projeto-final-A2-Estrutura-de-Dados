#ifndef RBT_H
#define RBT_H

#include <string>
#include "tree_utils.h" 

namespace RBT {
    
    // Cria uma nova árvore rbt
    BinaryTree* create();

    // Insere uma palavra com um id do documento
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);

    // Busca uma palavra na árvore
    SearchResult search(BinaryTree* tree, const std::string& word);

    // Libera memória da árvore
    void destroy(BinaryTree* tree);

    void leftRotate(BinaryTree* tree, Node* node, int& rotationsCount);
    void rightRotate(BinaryTree* tree, Node* node, int& rotationsCount);
    void fixInsertion(BinaryTree* tree, Node* node, int& rotationsCount);
    void destroyNode(Node* node, Node* NIL);


} //namespace RBT

#endif // RBT_H
