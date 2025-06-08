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

    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId){
        //Faz as inicializações necessárias
        auto start = std::chrono::high_resolution_clock::now();
        int comparisons = 0;

        Node* node = tree->root;
        Node* parent = nullptr;

    
        while (node != tree->NIL) {
            comparisons++;
            //Verifica se existe um nó com o mesmo valor na árvore
            if (word == node->word) {
                //Adiciona ao vetor de documentos caso já não tenha sido adicionado
                if (std::count(node->documentIds.begin(), node->documentIds.end(), documentId) == 0)
                    node->documentIds.push_back(documentId);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> duration_ms = end - start;
                double time_ms = duration_ms.count();
                return {comparisons, time_ms};
            }
            //Busca onde o nó deve ser adicionado
            parent = node;
            if (word < node->word) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        //Cria e adiciona o novo nó na árvore
        Node* newNode = new Node;
        newNode->word = word;
        newNode->documentIds.push_back(documentId);
        newNode->left = tree->NIL;
        newNode->right = tree->NIL;
        newNode->parent = parent;
        newNode->isRed = 1;

        if (parent == nullptr) 
        {tree->root = newNode;} 
        else if (word < parent->word) 
        {parent->left = newNode;}
         else 
        {parent->right = newNode;}
        
        // Corrige a árvore após a inserção
        fixInsertion(tree, newNode);

        //Calcula o tempo de inserção e retorna
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        double time_ms = duration_ms.count();
        return {comparisons, time_ms};
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
            } else {
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
    
    void destroy(BinaryTree* tree){
    if(tree != nullptr){
        destroyNode(tree->root);
        delete tree;
    }
    }

}
