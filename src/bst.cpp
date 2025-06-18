#include "bst.h"
#include <algorithm>


namespace BST
{
      BinaryTree* create() {
        BinaryTree* tree = new BinaryTree;
        tree->root = nullptr;
        tree->NIL = nullptr; // Não usado em BST
        return tree;
    }
    
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    // Inicia o cronômetro
    auto start = std::chrono::high_resolution_clock::now();   
    int comparisons = 0;

    Node* node = tree->root;
    Node* parent = nullptr;

    while (node != nullptr) {
        comparisons++;
        if (word == node->word) {
            if (std::count(node->documentIds.begin(), node->documentIds.end(), documentId) == 0)
                node->documentIds.push_back(documentId);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration_ms = end - start;
            double time_ms = duration_ms.count();
            return {comparisons, time_ms};
        }

        parent = node;
        if (word < node->word) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    // Criar novo nó
    Node* newNode = new Node;
    newNode->word = word;
    newNode->documentIds.push_back(documentId);
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = parent;
    // newNode->height = 1;
    // newNode->isRed = 0;

    if (parent == nullptr) {
        tree->root = newNode;
    } else if (word < parent->word) {
        parent->left = newNode;
    } else {
            parent->right = newNode;
        }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;
    double time_ms = duration_ms.count();
    return {comparisons, time_ms};
    }

    void destroy(BinaryTree* tree){
        if(tree != nullptr){
            destroyNode(tree->root);
            delete tree;
        }
    }
} // namespace BST
