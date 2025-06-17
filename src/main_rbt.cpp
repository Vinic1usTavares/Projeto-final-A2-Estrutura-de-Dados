#include "rbt.h"
#include "data.h"
#include "test.h"
#include "tree_utils.h"
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./bin/bst <search|stats> <n_docs> <diretorio>\n";
        std::cerr << "     ./bin/bst tests   (roda os testes unitários)\n";
        return 1;
    }

    std::string command = argv[1];

    // Caso de testes
    if(command == "tests") {
        //run_rbt_tests();
        return 0;
    }

    int n_docs = std::stoi(argv[2]);
    std::string dir = argv[3];

    BinaryTree* tree = RBT::create();

    auto start_index = std::chrono::high_resolution_clock::now();
    auto documents = load_documents(dir, n_docs);
    std::vector<InsertResult> insert_results = index_documents(tree, documents, RBT::insert);
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
            SearchResult result = search(tree, query);
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
        std::size_t TreeMemory = calculateTreeMemory(tree->root);
        double worstTime = measureWorstCase(tree);
        int minPath = findMinPath(tree, tree->root);
        int height  = (tree->root ? GetHeight(tree->root) : 0);

        double time_insertion = 0;
        int total_comparisons = 0;
        int total_rotations = 0;
        for (const auto& res : insert_results) {
            total_comparisons += res.numComparisons;
            total_rotations += res.rotationsCount;
            time_insertion += res.executionTime;
        }

    std::cout << "\n=== Estatísticas RBT ===\n";
    // --- Indexação ---
    std::cout << "-- Indexação / Inserção --\n";
    std::cout << "Documentos indexados:       " << n_docs << "\n";
    std::cout << "Tempo total de indexação (com inserção):   " << index_time.count() << " s\n";
    std::cout << "Tempo total de inserção:   " << time_insertion / 1000 << " s\n";
    std::cout << "Tempo médio de inserção (ms):   " << 
    
                time_insertion/n_docs << " ms\n\n";

    // --- Desempenho ---
    std::cout << "-- Desempenho --\n";
    std::cout << "Tempo médio de busca pior caso:    " << worstTime << " ms\n";
    std::cout << "Comparações (inserção):     " << total_comparisons << "\n";
    std::cout << "Total de rotações:          " << total_rotations << "\n\n";

    // --- Estrutura & Memória ---
    std::cout << "-- Estrutura & Memória --\n";
    std::cout << "Menor caminho:             " << minPath << "\n";
    std::cout << "Altura da árvore (maior caminho):          " 
    << height << "\n";
    std::cout << "Memória utilizada:         "
   
            << (TreeMemory / (1024.0 * 1024.0)) << " MB\n\n";



    }


    RBT::destroy(tree);
    return 0;
}


