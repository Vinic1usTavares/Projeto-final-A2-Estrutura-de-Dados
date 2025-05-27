#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <ctime>

// Estruturas
struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // usado na AVL
    int isRed;     // usado na RBT
};

struct BinaryTree {
    Node* root;
    Node* NIL; // usado na RBT (opcional)
};

struct InsertResult {
    int numComparisons;
    double executionTime;
};

struct SearchResult {
    int found;
    std::vector<int> documentIds;
    double executionTime;
    int numComparisons;
};

// Funções

void printIndexAux(Node* node, int& count, int max);
void printIndex(BinaryTree* tree);
void printTree(BinaryTree* tree);
Node* createNode();
void destroyNode(Node* node);


#endif