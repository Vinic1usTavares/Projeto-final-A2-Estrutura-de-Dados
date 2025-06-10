#include "avl.h"
#include "data.h"
#include "test.h"
#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./bin/avl <search|stats> <n_docs> <diretorio>\n";
        std::cerr << "     ./bin/avl tests   (roda os testes unitários)\n";
        return 1;
    }

    std::string command = argv[1];

    // Caso de testes
    if(command == "tests") {
        //run_avl_tests();
        return 0;
    }

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
        bool running = true;
        while (running) {
            std::cout << "Digite --quit para abortar a execucao." << std::endl;
            std::cout << "Digite uma palavra para buscar: ";
            std::cin >> query;
            if(query == "--quit") {
                running = false;
                break;
            }
            SearchResult result = AVL::search(tree, query);
            if(result.found == 0) {
                std::cout << query << " nao esta presente nos textos \n";
            } else {
                std::cout << "A palavra: \"" << query << "\" foi encontrada em " 
                          << result.documentIds.size() << " documento(s): ";
                for(size_t i = 0; i < result.documentIds.size(); ++i) {
                    std::cout << result.documentIds[i];
                    if(i < result.documentIds.size() - 1) std::cout << ',';
                }
                std::cout << ",\nTempo total da busca: " << result.executionTime << " ms \n";
                std::cout << "Total de comparacoes feitas: " << result.numComparisons << "\n";
                std::cout << std::endl;
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

    }

    AVL::destroy(tree);
    return 0;
}