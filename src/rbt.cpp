#include "rbt.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

namespace RBT {

    // Ponteiro global para o nó sentinela NIL (equivalente a nullptr nas folhas)
    Node* NIL = nullptr;

    // Criação da estrutura inicial da árvore
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

    // Rotação à esquerda
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

    // Rotação à direita
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

    // Corrige as violações das propriedades da árvore após inserção
    void fixInsertion(BinaryTree* tree, Node* node) {
        while (node != tree->root && node->parent->isRed) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                if (uncle->isRed) {
                    // Caso 1: Tio vermelho - recoloração
                    parent->isRed = 0;
                    uncle->isRed = 0;
                    grandparent->isRed = 1;
                    node = grandparent;
                } else {
                    // Casos 2 e 3: Tio preto - rotação e recoloração
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
        tree->root->isRed = 0; // raiz sempre preta
    }

    // Função principal de inserção
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
        auto start = std::chrono::high_resolution_clock::now();
        int comparisons = 0;

        Node* newNode = new Node;
        newNode->word = word;
        newNode->documentIds.push_back(documentId);
        newNode->isRed = 1;
        newNode->left = newNode->right = newNode->parent = tree->NIL;

        Node* parent = nullptr;
        Node* current = tree->root;

        while (current != tree->NIL) {
            parent = current;
            comparisons++;
            if (word < current->word) {
                current = current->left;
            } else if (word > current->word) {
                current = current->right;
            } else {
                // Palavra já existe: adiciona documento se for diferente
                if (current->documentIds.empty() || current->documentIds.back() != documentId)
                    current->documentIds.push_back(documentId);

                auto end = std::chrono::high_resolution_clock::now();
                return {comparisons, std::chrono::duration<double, std::milli>(end - start).count()};
            }
        }

        newNode->parent = parent;

        if (parent == nullptr) {
            tree->root = newNode;
        } else if (word < parent->word) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixInsertion(tree, newNode);

        auto end = std::chrono::high_resolution_clock::now();
        return {comparisons, std::chrono::duration<double, std::milli>(end - start).count()};
    }

    // Busca por uma palavra na árvore
    SearchResult search(BinaryTree* tree, const std::string& word) {
        auto start = std::chrono::high_resolution_clock::now();   
        int comparisons = 0;
        Node* node = tree->root;

        while (node != tree->NIL) {
            comparisons++;
            if (word == node->word) {
                auto end = std::chrono::high_resolution_clock::now();
                return {1, node->documentIds, std::chrono::duration<double, std::milli>(end - start).count(), comparisons};
            }

            node = (word < node->word) ? node->left : node->right;
        }

        auto end = std::chrono::high_resolution_clock::now();
        return {0, {}, std::chrono::duration<double, std::milli>(end - start).count(), comparisons};
    }

    // Função auxiliar recursiva para liberar nós da árvore
    void destroyNode(Node* node, Node* NIL) {
        if (node == NIL) return;
        destroyNode(node->left, NIL);
        destroyNode(node->right, NIL);
        delete node;
    }

    // Liberação de toda a memória alocada para a árvore
    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        destroyNode(tree->root, tree->NIL);
        delete tree;
    }
}
