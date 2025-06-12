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
            } 
            else {
                Node* uncle = grandparent->left;

                if (uncle->isRed) {
                    parent->isRed = 0;
                    uncle->isRed = 0;
                    grandparent->isRed = 1;
                    node = grandparent;
                } 
                else {
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
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;

    // Cria novo nó
    Node* newNode = new Node;
    newNode->word = word;
    newNode->documentIds.push_back(documentId);
    newNode->isRed = 1;
    newNode->left = newNode->right = newNode->parent = tree->NIL;

    // Percorre a árvore para inserir
    Node* parent = nullptr;
    Node* current = tree->root;

    while (current != tree->NIL) {
        parent = current;
        comparisons++;
        if (word < current->word) {
            current = current->left;
        } 
        else if (word > current->word) {
            current = current->right;
        } 
        else {
            // Palavra já existe, só adiciona docId se não for repetido
            if (current->documentIds.empty() || current->documentIds.back() != documentId)
                current->documentIds.push_back(documentId);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            return {comparisons, duration.count()};
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
    // Corrige a árvore após a inserção
    fixInsertion(tree, newNode);

    //Calcula o tempo de inserção e retorn
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {comparisons, duration.count()};
}

    SearchResult search(BinaryTree* tree, const std::string& word) {
        // Inicia o cronômetro
        auto start = std::chrono::high_resolution_clock::now();   
        int comparisons = 0;
        Node* node = tree->root;
        
        while(node != tree->NIL) {
            comparisons++;
            if(word == node->word) {
                // Para o cronômetro quando encontra a palavra
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration_ms = end - start;
                double time_ms = duration_ms.count();
                SearchResult result = {1, node->documentIds, time_ms, comparisons};
                return result;
            }
            
            
            if(word < node->word) {
                node = node->left;
            } 
            else {
                node = node->right;
            }
        }
        
        // Para o cronômetro quando não encontra a palavra
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        double time_ms = duration_ms.count();
        
        SearchResult result = {0, {}, time_ms, comparisons};
        return result;
    }

    void destroyNode(Node* node, Node* NIL) {
    if (node == NIL) { return; }
    destroyNode(node->left, NIL);
    destroyNode(node->right, NIL);
    delete node;
}

    void destroy(BinaryTree* tree) {
        if (tree == nullptr) { return; }
        destroyNode(tree->root, tree->NIL);
        delete tree;
    }
    
}


