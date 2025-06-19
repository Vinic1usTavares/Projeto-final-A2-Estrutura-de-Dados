#include "tree_utils.h"
#include <iostream>
#include <functional>
#include <queue>

SearchResult search(BinaryTree* tree, const std::string& word) {
    // Inicia o cronômetro
    auto start = std::chrono::high_resolution_clock::now();   
    int comparisons = 0;
    Node* node = tree->root;
    
    while(node != nullptr) {
        comparisons++;
        if(word == node->word) {
            // Para o cronômetro quando encontra a palavra
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration_ms = end - start;
            double time_ms = duration_ms.count();
            SearchResult result = {1, node->documentIds, time_ms, comparisons};
            return result;
        }
        
        // Ordem lexicográfica
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

// Função auxiliar recursiva para imprimir as palavras e seus IDs de documentos em ordem
void printIndexAux(Node* node, int& count, int max) {
    if (node != nullptr && count < max) {
        // Percorre a subárvore esquerda
        printIndexAux(node->left, count, max);

        // Imprime a palavra e os documentos associados
        count++;
        std::cout << count << ". " << node->word << ": ";

        for (size_t i = 0; i < node->documentIds.size(); ++i) {
            std::cout << node->documentIds[i];
            if (i < node->documentIds.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << '\n';

        // Percorre a subárvore direita
        printIndexAux(node->right, count, max);
    }
}

// Função que inicia a impressão do índice da árvore (limite de 50 palavras)
void printIndex(BinaryTree* tree) {
    int count = 0;
    printIndexAux(tree->root, count, 50);
}

// Cria e inicializa um novo nó com valores padrão
Node* createNode() {
    Node* node = new Node;
    node->word = "";
    node->documentIds = {};
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    node->height = 1;
    node->isRed = 0;
    return node;
}

// Libera recursivamente a memória de todos os nós da árvore
void destroyNode(Node* node) {
    if (node != nullptr) {
        destroyNode(node->left);
        destroyNode(node->right);
        delete node;
    }
}

// Função auxiliar recursiva para impressão visual da estrutura da árvore
void printTreeNode(Node* node, std::string prefix, bool isLeft) {
    if (node == nullptr) return;

    std::cout << prefix;
    std::cout << (isLeft ? u8"|-- " : u8"'-- ");
    std::cout << node->word << std::endl;

    std::string childPrefix = prefix + (isLeft ? u8"|   " : u8"    ");

    printTreeNode(node->left, childPrefix, true);
    printTreeNode(node->right, childPrefix, false);
}

// Inicia a impressão visual da árvore a partir da raiz
void printTree(BinaryTree* tree) {
    if (tree == nullptr) return; // Verifica se a árvore não é nula

    std::cout << tree->root->word << std::endl;
    printTreeNode(tree->root->left, "", true);
    printTreeNode(tree->root->right, "", false);
}

int GetHeight(Node* root){
    if (root == nullptr){
    return -1; 
    }
    int LeftHeight = GetHeight(root->left);
    int RightHeight = GetHeight(root->right);

    return 1 + std::max(LeftHeight, RightHeight);
}

//  Funções para cálculo de memória

std::size_t calculateNodeMemory(const Node* node) {
    if (node == nullptr) return 0;

    std::size_t memory = sizeof(Node); // Já inclui word, documentIds, left, right

    // Memória alocada dinamicamente pela string (se não estiver em SSO)
    if (node->word.capacity() > sizeof(node->word)) {
        memory += node->word.capacity();
    }

    // Memória alocada dinamicamente pelo vetor (se não estiver no buffer interno)
    memory += node->documentIds.capacity() * sizeof(int);

    return memory;
}

// Função recursiva para percorrer a árvore
std::size_t calculateTreeMemory(const Node* root) {
    if (root == nullptr) return 0;
    return calculateNodeMemory(root) 
           + calculateTreeMemory(root->left) 
           + calculateTreeMemory(root->right);
}


int findMinPath(BinaryTree* tree, Node* node) {
    if (node == nullptr || node == tree->NIL) {
        return 0;
    }
    int leftHeight = findMinPath(tree, node->left);
    int rightHeight = findMinPath(tree, node->right);
    return 1 + std::min(leftHeight, rightHeight);
}


Node* findDeepestNode(BinaryTree* tree) {
    if (tree->root == nullptr || tree->root == tree->NIL) return nullptr;

    std::queue<Node*> q; // Declara uma fila
    q.push(tree->root);
    Node* deepestNode = nullptr;

    while (!q.empty()) {
        deepestNode = q.front(); // Pega o nó da frente da fila
        q.pop(); // Remove o nó processado

        // Adiciona os filhos à fila
        if (deepestNode->left != nullptr && deepestNode->left != tree->NIL) {
            q.push(deepestNode->left);
        }
        if (deepestNode->right != nullptr && deepestNode->right != tree->NIL) {
            q.push(deepestNode->right);
        }
    }

    return deepestNode; // Retorna o último nó processado (mais profundo)
}

double measureDeepestNodeSearch(BinaryTree* tree) {
    Node* deepestNode = findDeepestNode(tree); // Implemente essa função
    double totalTime = 0.0;
    const int runs = 1000;

    for (int i = 0; i < runs; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        search(tree, deepestNode->word);
        auto end = std::chrono::high_resolution_clock::now();
        totalTime += std::chrono::duration<double, std::milli>(end - start).count();
    }
    return totalTime / runs;

}