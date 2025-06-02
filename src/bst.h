#ifndef BST_H
#define BST_H

#include "tree_utils.h"
#include <string>

namespace BST {
    BinaryTree* create();
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId);
    SearchResult search(BinaryTree* tree, const std::string& word);
    void destroy(BinaryTree* tree);
}

#endif
