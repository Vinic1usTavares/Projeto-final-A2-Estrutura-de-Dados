#include "tree_utils.h"
#include "data.h"
#include "bst.h"
#include "avl.h"
#include "rbt.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>

struct Acumulador {
    int total_comparacoes = 0;
    int total_operacoes = 0;
};

// Escreve uma linha no CSV com os dados atuais da árvore
void escrever_csv(std::ofstream& out, const std::string& nome_arvore, int num_docs,
                  BinaryTree* tree, const Acumulador& acc) {
    double media_comparacoes = acc.total_operacoes > 0
        ? static_cast<double>(acc.total_comparacoes) / acc.total_operacoes
        : 0.0;

    int altura = GetHeight(tree->root);
    int menor = findMinPath(tree, tree->root);

    out << nome_arvore << "," << num_docs << "," << media_comparacoes << ","
        << altura << "," << menor << "\n";
}

void benchmark_incremental(const std::string& nome_arvore,
                           BinaryTree* (*create_fn)(),
                           InsertResult (*insert_fn)(BinaryTree*, const std::string&, int),
                           void (*destroy_fn)(BinaryTree*),
                           const std::vector<std::pair<std::string, int>>& docs,
                           std::ofstream& out_csv) {
    
    BinaryTree* tree = create_fn();
    Acumulador acc;

    for (int i = 0; i < docs.size(); ++i) {
        auto palavras = process_words(docs[i].first);
        for (const auto& palavra : palavras) {
            InsertResult r = insert_fn(tree, palavra, docs[i].second);
            acc.total_comparacoes += r.numComparisons;
            acc.total_operacoes++;
        }

        int num_docs = i + 1;
        escrever_csv(out_csv, nome_arvore, num_docs, tree, acc);
    }

    destroy_fn(tree);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: ./comparativo_estrutural <diretorio_docs> <saida_csv>\n";
        return 1;
    }

    std::string dir_docs = argv[1];
    std::string csv_path = argv[2];

    auto docs = load_documents(dir_docs, 10000);

    std::ofstream out(csv_path);
    out << "arvore,num_docs,comparacoes_por_operacao,altura,menor_caminho\n";

    benchmark_incremental("bst", BST::create, BST::insert, BST::destroy, docs, out);
    benchmark_incremental("avl", AVL::create, AVL::insert, AVL::destroy, docs, out);
    benchmark_incremental("rbt", RBT::create, RBT::insert, RBT::destroy, docs, out);

    out.close();
    std::cout << "Resultados incrementais salvos em: " << csv_path << "\n";
    return 0;
}
