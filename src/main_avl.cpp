/**
 * @file main.cpp
 * @brief Programa principal para indexação e consulta de documentos usando Árvore AVL
 * 
 * Oferece dois modos de operação:
 * - search: Busca palavras no índice
 * - stats: Exibe estatísticas da indexação
 */

#include "avl.h"
#include "data.h"
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

/**
 * @brief Processa uma palavra removendo caracteres especiais e convertendo para minúsculas
 * @param word Palavra a ser processada
 * @return String limpa contendo apenas caracteres alfanuméricos em minúscula
 * @note Exemplo: "He'lLo!" → "hello"
 */
std::string process_word(const std::string& word) {
    std::string result;
    for (char c : word) {
        char lower_c = to_lower(c);
        if ((lower_c >= 'a' && lower_c <= 'z') || (lower_c >= '0' && lower_c <= '9')) {
            result += lower_c;
        }
    }
    return result;
}

/**
 * @brief Função principal do programa
 * @param argc Número de argumentos de linha de comando
 * @param argv Argumentos:
 *             [0] Nome do programa
 *             [1] Modo de operação ("search" ou "stats")
 *             [2] Número de documentos a indexar
 *             [3] Diretório contendo os documentos
 * @return 0 em caso de sucesso, 1 para erros de execução
 * 
 * @section workflow Fluxo de Execução
 * 1. Carrega documentos do diretório especificado
 * 2. Indexa conteúdo na AVL
 * 3. Executa o comando solicitado (busca ou estatísticas)
 * 
 * @section metrics Métricas Coletadas
 * - Tempo de indexação
 * - Número de comparações
 * - Altura da árvore
 */
int main(int argc, char* argv[]) {
    // Validação dos argumentos
    if (argc < 4) {
        std::cerr << "Uso: ./avl <search|stats> <n_docs> <diretorio>\n";
        return 1;
    }

    std::string command = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string dir = argv[3];

    // Inicialização da árvore
    BinaryTree* tree = AVL::create();

    // Fase de indexação com medição de tempo
    auto start_index = std::chrono::high_resolution_clock::now();
    auto documents = load_documents(dir, n_docs);
    std::vector<InsertResult> insert_results = index_documents(tree, documents, AVL::insert);
    auto end_index = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> index_time = end_index - start_index;

    // Modo de busca
    if (command == "search") {
        std::string query;
        std::cout << "Digite uma palavra para buscar: ";
        std::cin >> query;
        
        std::string clean_query = process_word(query);
        if (clean_query.empty()) {
            std::cout << "Palavra inválida após processamento.\n";
        } else {
            SearchResult result = AVL::search(tree, clean_query);
            if (result.found) {
                std::cout << "Palavra \"" << clean_query << "\" encontrada em " 
                          << result.documentIds.size() << " documento(s): ";
                for (size_t i = 0; i < result.documentIds.size(); ++i) {
                    std::cout << result.documentIds[i];
                    if (i < result.documentIds.size() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << "\nTempo de busca: " << result.executionTime << " ms\n";
                std::cout << "Comparações realizadas: " << result.numComparisons << "\n";
            } else {
                std::cout << "Palavra \"" << clean_query << "\" não encontrada.\n";
            }
        }
    } 
    // Modo de estatísticas
    else if (command == "stats") {
        int total_comparisons = 0;
        for (const auto& res : insert_results) {
            total_comparisons += res.numComparisons;
        }

        std::cout << "\n=== Estatísticas AVL ===\n";
        std::cout << "Documentos indexados: " << n_docs << "\n";
        std::cout << "Tempo total de indexação: " << index_time.count() << " segundos\n";
        std::cout << "Comparações totais (inserção): " << total_comparisons << "\n";
        std::cout << "Altura da árvore: " << (tree->root ? tree->root->height : 0) << "\n\n";

        std::cout << "=== Índice (amostra) ===\n";
        printIndex(tree);
    }

    // Liberação de recursos
    AVL::destroy(tree);
    return 0;
}