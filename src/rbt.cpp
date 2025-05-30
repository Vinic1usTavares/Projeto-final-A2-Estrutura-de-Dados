#include "rbt.h"
#include <iostream>

namespace RBT {

    Node* NIL = nullptr;

    BinaryTree* create() {
        if (NIL == nullptr) {
            NIL = new Node;
            NIL->isRed = 0;
            NIL->left = NIL->right = NIL->parent = nullptr;
        }

        BinaryTree* tree = new BinaryTree;
        tree->NIL = NIL;
        tree->root = NIL;
        return tree;
    }

    void leftRotate(BinaryTree* tree, Node* node) {
        Node* rightCurrentChild = node->right;
        node->right = rightCurrentChild->left;

        if (rightCurrentChild->left != nullptr) {
            rightCurrentChild->left->parent = node;
        }

        rightCurrentChild->parent = node->parent;

        if (node->parent == nullptr) {
            tree->root = rightCurrentChild;

        } else if (node == node->parent->left) {
            node->parent->left = rightCurrentChild;

        } else {
            node->parent->right = rightCurrentChild;

        }

        rightCurrentChild->left = node;
        node->parent = rightCurrentChild;

    }

    void rightRotate(BinaryTree* tree, Node* node) {
        Node* leftCurrentChild = node->left;
        node->left = leftCurrentChild->right;

        if (leftCurrentChild->left != nullptr) {
            leftCurrentChild->right->parent = node;
        }

        leftCurrentChild->parent = node->parent;

        if (node->parent == nullptr) {
            tree->root = leftCurrentChild;

        } else if (node == node->parent->left) {
            node->parent->left = leftCurrentChild;

        } else {
            node->parent->right = leftCurrentChild;

        }

        leftCurrentChild->right = node;
        node->parent = leftCurrentChild;

    }

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        
    }
 


}   