// avl.cpp
#include "avl.h"
#include "tree_utils.h"
#include <algorithm> // para std::max

namespace AVL {

BinaryTree* create() {
    BinaryTree* tree = new BinaryTree;
    tree->root = nullptr;
    tree->NIL = nullptr; 
    return tree;
}

// --- Funções Auxiliares AVL ---
int height(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

int balanceFactor(Node* node) {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

// --- Inserção AVL ---
Node* insertAux(Node* node, const std::string& word, int docId, int& comparisons) {
    if (node == nullptr) {
        Node* newNode = createNode();
        newNode->word = word;
        newNode->documentIds.push_back(docId);
        return newNode;
    }

    comparisons++;
    if (word < node->word) {
        node->left = insertAux(node->left, word, docId, comparisons);
    } else if (word > node->word) {
        node->right = insertAux(node->right, word, docId, comparisons);
    } else {
        // Palavra já existe: adiciona docId se necessário
        if (std::find(node->documentIds.begin(), node->documentIds.end(), docId) == node->documentIds.end()) {
            node->documentIds.push_back(docId);
        }
        return node;
    }

    // Atualiza altura do nó atual
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Calcula fator de balanceamento
    int balance = balanceFactor(node);

    // Casos de desbalanceamento
    // Esquerda-Esquerda
    if (balance > 1 && word < node->left->word) {
        return rotateRight(node);
    }
    // Direita-Direita
    if (balance < -1 && word > node->right->word) {
        return rotateLeft(node);
    }
    // Esquerda-Direita
    if (balance > 1 && word > node->left->word) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Direita-Esquerda
    if (balance < -1 && word < node->right->word) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

InsertResult insert(BinaryTree* tree, const std::string& word, int documentId) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;

    tree->root = insertAux(tree->root, word, documentId, comparisons);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {comparisons, duration.count()};
}

// --- Busca (igual à BST, mas dentro do namespace AVL) ---
SearchResult search(BinaryTree* tree, const std::string& word) {
    auto start = std::chrono::high_resolution_clock::now();
    int comparisons = 0;
    Node* node = tree->root;

    while (node != nullptr) {
        comparisons++;
        if (word == node->word) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            return {1, node->documentIds, duration.count(), comparisons};
        }

        if (word < node->word) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return {0, {}, duration.count(), comparisons};
}

void destroy(BinaryTree* tree) {
    if (tree != nullptr) {
        destroyNode(tree->root);
        delete tree;
    }
}

} // namespace AVL