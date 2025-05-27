#include "avl.h"
#include "data.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: ./avl <search|stats> <n_docs> <diretorio>\n";
        return 1;
    }

    std::string command = argv[1];
    int n_docs = std::stoi(argv[2]);
    std::string dir = argv[3];

    BinaryTree* tree = AVL::create();

    auto documents = load_documents(dir, n_docs);
    index_documents(tree, documents, AVL::insert);

    if (command == "search") {
        std::string query;
        std::cout << "Digite uma palavra para buscar: ";
        std::cin >> query;
        SearchResult result = AVL::search(tree, query);
        // imprimir resultado
    } else if (command == "stats") {
        // imprimir estatísticas
    }

    AVL::destroy(tree);
    return 0;
}
