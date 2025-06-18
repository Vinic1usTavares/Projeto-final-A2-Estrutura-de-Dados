#include "tree_utils.h"
#include <iostream>
#include <functional>

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

    std::size_t memory = 0;
    
    // Memória da palavra (string)
    memory += node->word.capacity() + sizeof(std::string);

    // Memória do vetor de documentIds
    memory += node->documentIds.capacity() * sizeof(int) + sizeof(std::vector<int>);

    // Memória da estrutura Node (inclui ponteiros left/right)
    memory += sizeof(Node);

    return memory;
}

// Função recursiva para percorrer a árvore
std::size_t calculateTreeMemory(const Node* root) {
    if (root == nullptr) return 0;
    return calculateNodeMemory(root) 
           + calculateTreeMemory(root->left) 
           + calculateTreeMemory(root->right);
}

// Retorna o tempo (em ms) da busca mais lenta (pior caso)
double calculateWorstCaseSearchTime(BinaryTree* tree) {
    double worstTime = 0.0;
    
    // Função para percorrer a árvore e testar cada palavra
    std::function<void(Node*)> testNode = [&](Node* node) {
        if (node == nullptr || node == tree->NIL) return;
        
        // Testa a busca para a palavra deste nó
        auto start = std::chrono::high_resolution_clock::now();
        search(tree, node->word);
        auto end = std::chrono::high_resolution_clock::now();
        double currentTime = std::chrono::duration<double, std::milli>(end - start).count();
        
        // Atualiza o pior tempo
        if (currentTime > worstTime) {
            worstTime = currentTime;
        }
        
        // Percorre os filhos
        testNode(node->left);
        testNode(node->right);
    };
    
    // Inicia o teste a partir da raiz
    testNode(tree->root);
    
    return worstTime;
}

double measureWorstCase(BinaryTree* tree, int repetitions) {
    double totalTime = 0.0;
    for (int i = 0; i < repetitions; ++i) {
        totalTime += calculateWorstCaseSearchTime(tree);
    }
    return totalTime / repetitions;
}

int findMinPath(BinaryTree* tree, Node* node) {
    if (node == nullptr || node == tree->NIL) {
        return 0;
    }
    int leftHeight = findMinPath(tree, node->left);
    int rightHeight = findMinPath(tree, node->right);
    return 1 + std::min(leftHeight, rightHeight);
}