#include "avl.h"
#include "data.h"
#include <iostream>
#include <string>
#include <chrono>  // Para medir tempo de indexação

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: ./avl <search|stats> <n_docs> <diretorio>\n";
        return 1;
    }

    std::string command = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string dir = argv[3];

    BinaryTree* tree = AVL::create();

    // Mede o tempo total de indexação
    auto start_index = std::chrono::high_resolution_clock::now();
    auto documents = load_documents(dir, n_docs);
    std::vector<InsertResult> insert_results = index_documents(tree, documents, AVL::insert);
    auto end_index = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> index_time = end_index - start_index;

    if (command == "search") {
        std::string query;
        std::cout << "Digite uma palavra para buscar: ";
        std::cin >> query;

        SearchResult result = AVL::search(tree, query);
        if (result.found) {
            std::cout << "Palavra \"" << query << "\" encontrada em " << result.documentIds.size() 
                      << " documento(s): ";
            for (int id : result.documentIds) {
                std::cout << id << " ";
            }
            std::cout << "\nTempo de busca: " << result.executionTime << " ms\n";
            std::cout << "Comparações realizadas: " << result.numComparisons << "\n";
        } else {
            std::cout << "Palavra \"" << query << "\" não encontrada.\n";
        }

    } else if (command == "stats") {
        // Estatísticas de indexação
        int total_comparisons = 0;
        for (const auto& res : insert_results) {
            total_comparisons += res.numComparisons;
        }

        std::cout << "\n=== Estatísticas AVL ===\n";
        std::cout << "Documentos indexados: " << n_docs << "\n";
        std::cout << "Tempo total de indexação: " << index_time.count() << " segundos\n";
        std::cout << "Comparações totais (inserção): " << total_comparisons << "\n";
        std::cout << "Altura da árvore: " << (tree->root ? tree->root->height : 0) << "\n\n";

        // Opcional: imprimir parte do índice (primeiras 20 palavras)
        std::cout << "=== Índice (amostra) ===\n";
        printIndex(tree);
    }

    AVL::destroy(tree);
    return 0;
}