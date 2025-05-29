#include "avl.h"
#include "data.h"
#include <iostream>
#include <string>
#include <chrono>
#include <vector>


// Função manual para processar palavras
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

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: ./avl <search|stats> <n_docs> <diretorio>\n";
        return 1;
    }

    std::string command = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string dir = argv[3];

    BinaryTree* tree = AVL::create();

    auto start_index = std::chrono::high_resolution_clock::now();
    auto documents = load_documents(dir, n_docs);
    std::vector<InsertResult> insert_results = index_documents(tree, documents, AVL::insert);
    auto end_index = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> index_time = end_index - start_index;

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

    AVL::destroy(tree);
    return 0;
}