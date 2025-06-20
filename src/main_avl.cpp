#include "avl.h"
#include "data.h"
#include "test.h"
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./bin/avl <search|stats> <n_docs> <diretorio>\n";
        std::cerr << "     ./bin/avl tests   (roda os testes unitários)\n";
        return 1;
    }

    std::string command = argv[1];

    // Comando inválido
    if (command != "search" && command != "stats" && command != "tests") {
        std::cerr << "Erro: comando invalido. Use 'search', 'stats' ou 'tests'.\n";
        return 1;
    }

    // Se for search ou stats, precisa de n_docs e diretorio
    if ((command == "search" || command == "stats") && argc < 4) {
        std::cerr << "Erro: argumentos insuficientes para o comando '" << command << "'.\n";
        std::cerr << "Uso: ./bin/bst <search|stats> <n_docs> <diretorio>\n";
        return 1;
    }

    // Checar se n_docs é inteiro > 0
    if (command == "search" || command == "stats") {
        try {
            int n_docs = std::stoi(argv[2]);
            if (n_docs <= 0) {
                std::cerr << "Erro: o numero de documentos deve ser um inteiro maior que zero.\n";
                return 1;
            }
        } catch (...) {
            std::cerr << "Erro: o argumento <n_docs> deve ser um numero inteiro valido.\n";
            return 1;
        }
    }

    // Caso de testes
    if(command == "tests") {
        run_avl_tests();
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
        double worstTime = measureDeepestNodeSearch(tree);
        int minPath = findMinPath(tree, tree->root);
        int numNodes = countNodes(tree->root);

        double time_insertion = 0;
        int total_comparisons = 0;
        int total_rotations =  0;
        for (const auto& res : insert_results) {
            total_comparisons += res.numComparisons;
            total_rotations += res.rotationsCount;
            time_insertion += res.executionTime;
        }

    std::cout << "\n=== Estatísticas AVL ===\n";
    // --- Indexação ---
    std::cout << "-- Indexação / Inserção --\n";
    std::cout << "Documentos indexados:                      " << documents.size() << "\n";
    std::cout << "Tempo total de indexação (com inserção):   " << index_time.count() << " s\n";
    std::cout << "Tempo total de inserção:                   " << time_insertion / 1000 << " s\n";
    std::cout << "Tempo médio de inserção (ms):              " << 
    
                time_insertion/n_docs << " ms\n\n";

    // --- Desempenho ---
    std::cout << "-- Desempenho --\n";
    std::cout << "Tempo médio de busca pior caso:    " << worstTime << " ms\n";
    std::cout << "Comparações (inserção):            " << total_comparisons << "\n";
    std::cout << "Total de rotações:                 " << total_rotations << "\n\n";

    // --- Estrutura & Memória ---
    std::cout << "-- Estrutura & Memória --\n";
    std::cout << "Menor caminho:                      " << minPath << "\n";
    std::cout << "Número total de nós:                " << numNodes << "\n";
    std::cout << "Altura da árvore (maior caminho):   " << tree->root->height << "\n";
    std::cout << "Memória utilizada:                  "
   
            << (TreeMemory / (1024.0 * 1024.0)) << " MB\n\n";



    //std::ofstream out("docs/estatisticas.csv", std::ios::app);

    //Cabeçalho: executar apenas na primeira vez
    //out << "arvore,num_docs,segundos_insercao,segundos_indexacao,pior_busca_ms,comparacoes,num_rotacoes,menor_caminho,altura,memoria_mb\n";

    // out << "AVL," 
    // << n_docs << ","
    // << (time_insertion / 1000) << ","
    // << index_time.count() << ","
    // << worstTime << ","
    // << total_comparisons << ","
    // << total_rotations << ","
    // << minPath << ","
    // << tree->root->height << ","
    // << (TreeMemory / (1024.0 * 1024.0)) 
    // << "\n";

    // out.close();

}
    AVL::destroy(tree);
    return 0;
}