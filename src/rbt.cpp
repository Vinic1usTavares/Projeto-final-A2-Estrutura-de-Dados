#include "rbt.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>


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

    // funções para rotacionar subárvores
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

        if (leftCurrentChild->right != nullptr) {
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

    void fixInsertion(BinaryTree* tree, Node* node) {
    while (node != tree->root && node->parent->isRed) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if (uncle->isRed) {
                parent->isRed = 0;
                uncle->isRed = 0;
                grandparent->isRed = 1;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    node = parent;
                    leftRotate(tree, node);
                    parent = node->parent;
                }
                parent->isRed = 0;
                grandparent->isRed = 1;
                rightRotate(tree, grandparent);
            }
        } else {
            Node* uncle = grandparent->left;

            if (uncle->isRed) {
                parent->isRed = 0;
                uncle->isRed = 0;
                grandparent->isRed = 1;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    node = parent;
                    rightRotate(tree, node);
                    parent = node->parent;
                }
                parent->isRed = 0;
                grandparent->isRed = 1;
                leftRotate(tree, grandparent);
            }
        }
    }
    tree->root->isRed = 0;
}
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    // TODO: implementar inserção na árvore rubro-negra
    return InsertResult{}; // valor de retorno temporário para compilar
}

    void destroyNode(Node* node, Node* NIL) {
    if (node == nullptr || node == NIL) return;
    destroyNode(node->left, NIL);
    destroyNode(node->right, NIL);
    delete node;
}

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        destroyNode(tree->root, tree->NIL);
        delete tree;
    }



}
