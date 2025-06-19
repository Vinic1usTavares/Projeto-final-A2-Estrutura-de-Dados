#include "tree_utils.h"
#include "data.h"
#include "bst.h"
#include "avl.h"
#include "rbt.h"
#include <fstream>
#include <chrono>
#include <functional>
#include <iostream>

void benchmark_incremental(const std::string& nome,
                           BinaryTree* (*create_fn)(),
                           InsertResult (*insert_fn)(BinaryTree*, const std::string&, int),
                           void (*destroy_fn)(BinaryTree*),
                           const std::vector<std::pair<std::string, int>>& docs,
                           std::ofstream& out_csv) {

    BinaryTree* tree = create_fn();
    double tempo_insercao_total = 0.0;
    int n = 0;

    auto start_total = std::chrono::high_resolution_clock::now();

    for (const auto& doc : docs) {
        auto palavras = process_words(doc.first);

        auto start_doc = std::chrono::high_resolution_clock::now();
        for (const std::string& palavra : palavras) {
            InsertResult r = insert_fn(tree, palavra, doc.second);
            tempo_insercao_total += r.executionTime / 1000.0; // milissegundos para segundos
        }
        auto end_doc = std::chrono::high_resolution_clock::now();

        ++n;
        std::chrono::duration<double> dur_index = end_doc - start_total;

        // Escreve linha no CSV
        out_csv << nome << "," << n << "," << tempo_insercao_total << "," << dur_index.count() << "\n";
    }

    destroy_fn(tree);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: ./benchmark <diretorio_docs> <saida_csv>\n";
        return 1;
    }

    std::string dir_docs = argv[1];
    std::string csv_path = argv[2];

    std::ofstream csv(csv_path);
    csv << "arvore,num_docs,segundos_insercao,segundos_indexacao\n";

    auto docs = load_documents(dir_docs, 10000);  // Carrega todos de uma vez

    benchmark_incremental("bst", BST::create, BST::insert, BST::destroy, docs, csv);
    benchmark_incremental("avl", AVL::create, AVL::insert, AVL::destroy, docs, csv);
    benchmark_incremental("rbt", RBT::create, RBT::insert, RBT::destroy, docs, csv);

    csv.close();
    std::cout << "Benchmark incremental concluído com sucesso.\n";
    return 0;
}
