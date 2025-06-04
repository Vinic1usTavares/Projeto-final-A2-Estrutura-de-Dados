#include "bst.h"
#include "data.h"
#include "test.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./bst <search|stats> <n_docs> <diretorio>\n";
        std::cerr << "     ./bst tests   (roda os testes unitários)\n";
        return 1;
}

    std::string command = argv[1];

    // Caso de testes
    if(command == "tests") {
        run_bst_tests();
        return 0;
    }

    int n_docs = std::stoi(argv[2]);
    std::string dir = argv[3];

    BinaryTree* tree = BST::create();

    auto documents = load_documents(dir, n_docs);
    std::vector<InsertResult> results = index_documents(tree, documents, BST::insert); // Estatísticas da geração da árvore

    if (command == "search") {
        std::string query;

        while (true) {
            std::cout << "Digite --quit para abortar a execução." << std::endl;
            std::cout << "Digite uma palavra para buscar: ";
            std::cin >> query;
            SearchResult result = BST::search(tree, query);
            if(result.found == 0) std::cout << query << " nao esta presente nos textos \n";
            else{
                std::cout << "A palavra: \"" << query << "\" foi encontrada em " << result.documentIds.size() << " documento(s): ";
                for(int id: result.documentIds) std::cout << id << ',';
                std::cout << "\nTempo total da busca: " << result.executionTime << " ms \n";
                std::cout << "Total de comparacoes feitas: " << result.numComparisons << "\n";
                std::cout << std::endl;
            }
        }
    } else if (command == "stats") {
        // imprimir estatísticas
        printIndex(tree);
    }
    

    BST::destroy(tree);
    return 0;
}
