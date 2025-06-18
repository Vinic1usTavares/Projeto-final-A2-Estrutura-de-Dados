#include "rbt.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

namespace RBT {

    // Ponteiro global para o nó sentinela NIL (equivalente a nullptr nas folhas)
    Node* NIL = nullptr;

    // Inicializa uma árvore vazia
    BinaryTree* create() {
        if (NIL == nullptr) {
            NIL = new Node;
            NIL->isRed = 0; // NIL é sempre preto
            NIL->left = NIL->right = NIL->parent = nullptr;
        }

        BinaryTree* tree = new BinaryTree;
        tree->NIL = NIL;
        tree->root = NIL; // Árvore vazia
        return tree;
    }

    // Rotação à esquerda
    void leftRotate(BinaryTree* tree, Node* node, int& rotationsCount) {
        rotationsCount ++;
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
    void rightRotate(BinaryTree* tree, Node* node, int& rotationsCount) {
        rotationsCount ++;
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

    // Corrige as violações às propriedades da RBT após a inserção de um nó
    void fixInsertion(BinaryTree* tree, Node* node, int& rotationsCount) {
        while (node != tree->root && node->parent->isRed) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            if (parent == grandparent->left) { // Caso esquerdo
                Node* uncle = grandparent->right;

                if (uncle->isRed) {  // Tio vermelho - recoloração
                    parent->isRed = 0;
                    uncle->isRed = 0;
                    grandparent->isRed = 1;
                    node = grandparent;
                } else {
                    // Casos 2 e 3: Tio preto - rotação e recoloração
                    if (node == parent->right) { // Verifica se está na direção oposta (rotação dupla)
                        node = parent;
                        leftRotate(tree, node, rotationsCount);
                        parent = node->parent;
                    }
                    parent->isRed = 0;
                    grandparent->isRed = 1;
                    rightRotate(tree, grandparent, rotationsCount);
                }
            } 
            else {  // Caso direito
                Node* uncle = grandparent->left;

                if (uncle->isRed) { // Tio vermelho: recolorir
                    parent->isRed = 0;
                    uncle->isRed = 0;
                    grandparent->isRed = 1;
                    node = grandparent;
                } 
                else { 
                    if (node == parent->left) { // Verifica se está na direção oposta (rotação dupla)
                        node = parent;
                        rightRotate(tree, node, rotationsCount);
                        parent = node->parent;
                    }
                    parent->isRed = 0;
                    grandparent->isRed = 1;
                    leftRotate(tree, grandparent, rotationsCount);
                }
            }
        }
        tree->root->isRed = 0; // raiz sempre preta
    }

    // Insere uma palavra na árvore RBT e retorna estatísticas da inserção
    InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;
    int rotationsCount = 0;

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
        } else if (word > current->word) {
            current = current->right;
        } else {
            // Palavra já existe, evita duplicar o docId
            if (current->documentIds.empty() || current->documentIds.back() != documentId) {
                current->documentIds.push_back(documentId);
            }

            auto end = std::chrono::high_resolution_clock::now();
            return {comparisons, std::chrono::duration<double, std::milli>(end - start).count(), 0};
        }
    }

    // Atribui o pai e insere na árvore
    newNode->parent = parent;
    if (parent == nullptr) {
        tree->root = newNode;
    } else if (word < parent->word) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Corrige a RBT após a inserção
    fixInsertion(tree, newNode, rotationsCount);

    auto end = std::chrono::high_resolution_clock::now();
    return {comparisons, std::chrono::duration<double, std::milli>(end - start).count(), rotationsCount};
}

    // Libera recursivamente a memória de todos os nós da árvore
    void destroyNode(Node* node, Node* NIL) {
    if (node == NIL) { return; }
    destroyNode(node->left, NIL);
    destroyNode(node->right, NIL);
    delete node;
}
    // Exclui a árvore e libera a memória que ela ocupava
    void destroy(BinaryTree* tree) {
        if (tree == nullptr) return;
        destroyNode(tree->root, tree->NIL);
        delete tree;
    }
    
    //Checa se a árvore não tem pai e filho simultaneamente vermelhos
    bool checkRedProperty(Node* node, Node* NIL) {
    if (node == NIL) return true;
    if (node->isRed) {
        if (node->left->isRed || node->right->isRed)
            return false;
    }
    return checkRedProperty(node->left, NIL) && checkRedProperty(node->right, NIL);
}
    //Calcula o blackheight de uma rbt
    int blackHeight(Node* node, Node* NIL) {
    if (node == NIL) return 1; // Contabiliza NIL como preto
    int leftBlackHeight = blackHeight(node->left, NIL);
    int rightBlackHeight = blackHeight(node->right, NIL);
    if (leftBlackHeight == 0 || rightBlackHeight == 0) return 0;
    if (leftBlackHeight != rightBlackHeight) return 0;
    return leftBlackHeight + (node->isRed ? 0 : 1);
}

    
}
