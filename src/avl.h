#ifndef AVL_H
#define AVL_H

#include "tree_utils.h"
#include <string>

namespace AVL {
    BinaryTree* create();
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroy(BinaryTree* tree);
}

#endif