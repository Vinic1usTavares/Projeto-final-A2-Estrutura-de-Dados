#include "avl.h"
#include "data.h"
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

// Função para processar palavras, removendo caracteres especiais e convertendo para minúsculas
std::string process_word(const std::string& word) {
    std::string result;
    for (char c : word) {
        char lower_c = to_lower(c);  // Converte para minúscula
        if ((lower_c >= 'a' && lower_c <= 'z') || (lower_c >= '0' && lower_c <= '9')) {
            result += lower_c; // Mantém apenas letras e números
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    // Verifica se os argumentos necessários foram passados
    if (argc < 4) {
        std::cerr << "Uso: ./main_avl <search|stats> <n_docs> <diretorio>\n";
        return 1;
    }

    // Lê os argumentos da linha de comando
    std::string command = argv[1];      // Comando: "search" ou "stats"
    int n_docs = std::stoi(argv[2]);    // Número de documentos a serem indexados
    std::string dir = argv[3];          // Diretório contendo os documentos

    // Cria uma árvore AVL
    BinaryTree* tree = AVL::create();

    // Inicia o cronômetro para medir o tempo de indexação
    auto start_index = std::chrono::high_resolution_clock::now();

    // Carrega os documentos do diretório especificado
    auto documents = load_documents(dir, n_docs);

    // Indexa os documentos na árvore AVL
    std::vector<InsertResult> insert_results = index_documents(tree, documents, AVL::insert);

    // Finaliza a medição de tempo
    auto end_index = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> index_time = end_index - start_index;

    // Se o comando for de busca de palavra
    if (command == "search") {
        std::string query;
        std::cout << "Digite uma palavra para buscar: ";
        std::cin >> query;

        // Processa a palavra para remoção de caracteres inválidos
        std::string clean_query = process_word(query);
        if (clean_query.empty()) {
            std::cout << "Palavra inválida após processamento.\n";
        } else {
            // Realiza a busca na árvore AVL
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
    // Se o comando for para mostrar estatísticas
    else if (command == "stats") {
        int total_comparisons = 0;
        for (const auto& res : insert_results) {
            total_comparisons += res.numComparisons;  // Soma o total de comparações feitas
        }

        // Exibe estatísticas gerais sobre a árvore AVL
        std::cout << "\n=== Estatísticas AVL ===\n";
        std::cout << "Documentos indexados: " << n_docs << "\n";
        std::cout << "Tempo total de indexação: " << index_time.count() << " segundos\n";
        std::cout << "Comparações totais (inserção): " << total_comparisons << "\n";
        std::cout << "Altura da árvore: " << (tree->root ? tree->root->height : 0) << "\n\n";

        std::cout << "=== Índice (amostra) ===\n";
        //printIndex(tree);  // Mostra as primeiras 50 palavras indexadas, caso queria velas
        //printTree(tree); //Printa a arvore
    }

    // Destroi a árvore AVL liberando a memória alocada
    AVL::destroy(tree);
    return 0;
}
