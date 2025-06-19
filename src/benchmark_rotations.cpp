#include "tree_utils.h"
#include "data.h"
#include "avl.h"
#include "rbt.h"
#include <fstream>
#include <iostream>
#include <vector>

struct Acumulador {
    int total_rotacoes = 0;
    int total_operacoes = 0;
};

// Escreve no CSV os dados de rotações + altura
void escrever_csv(std::ofstream& out, const std::string& nome_arvore, int num_docs,
                  BinaryTree* tree, const Acumulador& acc) {
    double rotacoes_por_operacao = acc.total_operacoes > 0
        ? static_cast<double>(acc.total_rotacoes) / acc.total_operacoes
        : 0.0;

    int altura = GetHeight(tree->root);
    int menor = findMinPath(tree, tree->root);

    out << nome_arvore << "," << num_docs << "," << rotacoes_por_operacao << ","
        << acc.total_rotacoes << "," << altura << "," << menor << "\n";
}

void benchmark_rotations_incremental(const std::string& nome_arvore,
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
            acc.total_rotacoes += r.rotationsCount;
            acc.total_operacoes++;
        }

        int num_docs = i + 1;
        escrever_csv(out_csv, nome_arvore, num_docs, tree, acc);
    }

    destroy_fn(tree);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: ./benchmark_rotations_incremental <diretorio_docs> <saida_csv>\n";
        return 1;
    }

    std::string dir_docs = argv[1];
    std::string csv_path = argv[2];

    auto docs = load_documents(dir_docs, 10000);

    std::ofstream out(csv_path);
    out << "arvore,num_docs,rotacoes_por_operacao,rotacoes_totais,altura,menor_caminho\n";

    benchmark_rotations_incremental("avl", AVL::create, AVL::insert, AVL::destroy, docs, out);
    benchmark_rotations_incremental("rbt", RBT::create, RBT::insert, RBT::destroy, docs, out);

    out.close();
    std::cout << "Benchmark incremental de rotações concluído. Resultados salvos em: " << csv_path << "\n";
    return 0;
}
