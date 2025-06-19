#ifndef TREE_UTILS_H
#define TREE_UTILS_H

#include <vector>
#include <string>
#include <iostream>
#include <chrono>

// Estrutura que representa um nó de uma árvore binária
struct Node {
    std::string word;               // Palavra armazenada no nó
    std::vector<int> documentIds;   // IDs dos documentos onde a palavra aparece
    Node* parent;                   // Ponteiro para o nó pai
    Node* left;                     // Ponteiro para o filho esquerdo
    Node* right;                    // Ponteiro para o filho direito
    int height;                     // Altura do nó (usado em árvores AVL)
    int isRed;                      // Indica se o nó é vermelho (usado em árvores rubro-negras)
};

// Estrutura que representa uma árvore binária
struct BinaryTree {
    Node* root;  // Raiz da árvore
    Node* NIL;   // Nó sentinela (usado em RBT, pode ser ignorado para AVL)
};

// Resultado da inserção de uma palavra na árvore
struct InsertResult {
    int numComparisons;    // Número de comparações realizadas
    double executionTime;  // Tempo gasto na inserção (em milissegundos)
    int rotationsCount;
};

// Resultado da busca por uma palavra na árvore
struct SearchResult {
    int found;                      // Indica se a palavra foi encontrada (1) ou não (0)
    std::vector<int> documentIds;  // Lista de IDs dos documentos encontrados
    double executionTime;          // Tempo da busca (em milissegundos)
    int numComparisons;            // Número de comparações realizadas durante a busca
};

/**
 * Pesquisa uma palavra na árvore.
 * @param tree Endereço da árvore
 * @param word Palavra a ser pesquisada
 * @return SearchResult contendo: found = 1 caso a palvra for achada ou 0 caso contrário, um vector<int> dos Ids dos documentos em que a palvra esta presente, o tempo (double) de execução da função e o número (int) de comparações realizadas.
 */
SearchResult search(BinaryTree* tree, const std::string& word);

/**
 * @brief Função auxiliar para impressão recursiva do índice em ordem lexicográfica.
 * 
 * @param node Nó atual sendo processado (inicia na raiz).
 * @param count Referência ao contador de palavras impressas (incrementado recursivamente).
 * @param max Número máximo de palavras a serem impressas (limite para evitar sobrecarga).
 * 
 * @note Esta função é para uso interno da printIndex() e não deve ser chamada diretamente.
 */
void printIndexAux(Node* node, int& count, int max);

/**
 * @brief Imprime até 50 palavras do índice com seus documentos associados.
 * 
 * @param tree Ponteiro para a árvore contendo o índice.
 * 
 * @details Percorre a árvore em-ordem, imprimindo:
 *          [contador]. palavra: doc1, doc2, ...
 *          Limitado a 50 entradas para evitar sobrecarga de saída.
 */
void printIndex(BinaryTree* tree);

/**
 * @brief Imprime representação visual da estrutura da árvore (diagrama horizontal).
 * 
 * @param tree Ponteiro para a árvore a ser visualizada.
 * 
 * @example
 *   raiz
 *   |-- esquerda
 *   |   |-- sub-esquerda
 *   '-- direita
 * 
 * @note Útil para depuração e análise de estrutura. Não usar em árvores muito grandes.
 */
void printTree(BinaryTree* tree);

/**
 * @brief Factory function para criação de nós.
 * 
 * @return Node* Novo nó alocado na memória com valores padrão:
 *         - word: string vazia
 *         - documentIds: vetor vazio
 *         - ponteiros: nullptr
 *         - height: 1
 *         - isRed: 0 (preto)
 */
Node* createNode();

/**
 * @brief Destrói recursivamente uma subárvore a partir de um nó.
 * 
 * @param node Raiz da subárvore a ser destruída (percurso pós-ordem).
 * 
 * @warning Não usar para destruir árvores completas - prefira destroy() específica (RBT::destroy/AVL::destroy).
 */
void destroyNode(Node* node);

/**
 * @brief Calcula a altura de uma subárvore.
 * 
 * @param root Raiz da subárvore (nullptr considerado altura -1).
 * @return int Altura máxima da árvore (0 para nó único, -1 para árvore vazia).
 * 
 * @note Baseado em percurso recursivo pós-ordem.
 */
int GetHeight(Node* root);

/**
 * @brief Calcula consumo de memória de um nó individual.
 * 
 * @param node Nó a ser analisado (nullptr retorna 0).
 * @return std::size_t Total de bytes utilizados, incluindo:
 *         - Tamanho da estrutura Node
 *         - Alocação interna da string (word)
 *         - Alocação do vetor (documentIds)
 */
std::size_t calculateNodeMemory(const Node* node);

/**
 * @brief Calcula consumo total de memória de uma subárvore.
 * 
 * @param root Raiz da subárvore (nullptr retorna 0).
 * @return std::size_t Soma recursiva da memória de todos os nós.
 * 
 * @see calculateNodeMemory()
 */
std::size_t calculateTreeMemory(const Node* root);

/**
 * @brief Calcula a altura do menor caminho da raiz até uma folha.
 * 
 * @param tree Árvore contendo o nó (para acesso ao NIL se aplicável).
 * @param node Nó raiz da subárvore (nullptr retorna 0).
 * @return int Altura do caminho mínimo (0 se nó for folha).
 * 
 * @note Útil para verificar balanceamento da árvore.
 */
int findMinPath(BinaryTree* tree, Node* node);

/**
 * @brief Encontra o nó mais profundo da árvore binária.
 * 
 * @param tree Ponteiro para a estrutura da árvore binária (contendo raiz e NIL).
 * @return Node* Ponteiro para o nó mais profundo (nullptr se árvore vazia).
 * 
 * @note Implementa uma BFS (Busca em Largura) usando std::queue.
 * O nó mais profundo representa o pior caso teórico de busca na árvore.
 */
Node* findDeepestNode(BinaryTree* tree);

/**
 * @brief Mede o tempo médio de busca para o nó mais profundo da árvore.
 * 
 * @param tree Ponteiro para a estrutura da árvore binária.
 * @return double Tempo médio em milissegundos (baseado em 1000 execuções).
 * 
 * @note Utiliza findDeepestNode() para identificar o pior caso estrutural.
 * Realiza múltiplas execuções para reduzir variações de medição.
 * Retorna -1.0 se a árvore estiver vazia.
 */
double measureDeepestNodeSearch(BinaryTree* tree);

/**
 * @brief Conta o número total de nós em uma árvore binária.
 * 
 * @tparam NodePtr Tipo do ponteiro de nó (deve ser compatível com left/right).
 * @param root Ponteiro para a raiz da árvore ou subárvore a ser contada.
 * @param NIL Ponteiro para o nó sentinela (folha) utilizado na árvore (opcional).
 * @return int Número total de nós na árvore/subárvore.
 * 
 * @note Esta função é genérica e funciona com diferentes implementações de árvores:
 * - BST: usar countNodes<BST::Node*>(root)
 * - AVL: usar countNodes<AVL::Node*>(root) 
 * - RBT: usar countNodes<RBT::Node*>(root, tree->NIL)
 * 
 * @note Complexidade: O(n) onde n é o número de nós (visita cada nó exatamente uma vez)
 * @note Espaço: O(h) onde h é a altura da árvore (devido à recursão)
 * 
 * @warning Para árvores muito desbalanceadas, considere usar a versão iterativa
 *          para evitar possível estouro de pilha (stack overflow).
 * 
 * @code
 * // Exemplo para BST (usa nullptr como folha):
 * int total = countNodes<BST::Node*>(bst->root);
 * 
 * // Exemplo para RBT (usa NIL como folha):
 * int total = countNodes<RBT::Node*>(rbt->root, rbt->NIL);
 * @endcode
 */
template <typename NodePtr>
int countNodes(NodePtr root, NodePtr NIL = nullptr) {
    if (root == nullptr || root == NIL) {
        return 0;
    }
    return 1 + countNodes(root->left, NIL) 
             + countNodes(root->right, NIL);
}

#endif
