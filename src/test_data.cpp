#include <cassert>
#include <iostream>
#include "bst.h"
#include "data.h"
#include "tree_utils.h"

using namespace BST;

// Teste 1: process_words
void test_process_words() {
    std::cout << "[TESTE] Normalizacao e separacao de palavras...\n";

    std::cout << "  1. Definindo string de entrada:\n";
    std::cout << "     std::string texto = \"Chuvisca muito em Garlgalo Nobre\";\n";
    std::string texto = "Chuvisca muito em Garlgalo Nobre";

    std::cout << "  2. Chamando: std::vector<std::string> resultado = process_words(texto);\n";
    std::vector<std::string> resultado = process_words(texto);

    std::cout << "  3. Verificando se as palavras foram processadas corretamente...\n";
    assert(resultado.size() == 5);
    assert(resultado[0] == "chuvisca");
    assert(resultado[1] == "muito");
    assert(resultado[2] == "em");
    assert(resultado[3] == "garlgalo");
    assert(resultado[4] == "nobre");

    std::cout << "     -> OK: Texto processado e normalizado corretamente\n";
    std::cout << "Teste concluido com sucesso: funcao 'process_words' validada.\n";
    std::cout << std::string(60, '-') << "\n";
}

// Teste 2: index_documents com funcao insert da BST
void test_index_documents() {
    std::cout << "[TESTE] Indexacao de documentos com insercao na arvore...\n";

    std::cout << "  1. Definindo vetor de documentos:\n";
    std::cout << "     std::vector<std::pair<std::string, int>> docs = {\n";
    std::cout << "         {\"Chuvisca muito em Garlgalo Nobre\", 1},\n";
    std::cout << "         {\"Garlgalo continua muito nobre\", 2}\n";
    std::cout << "     };\n";

    std::vector<std::pair<std::string, int>> docs = {
        {"Chuvisca muito em Garlgalo Nobre", 1},
        {"Garlgalo continua muito nobre", 2}
    };

    std::cout << "  2. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  3. Chamando: auto resultados = index_documents(tree, docs, insert);\n";
    auto resultados = index_documents(tree, docs, insert);

    std::cout << "  4. Chamando: SearchResult res = search(tree, \"garlgalo\");\n";
    SearchResult res = search(tree, "garlgalo");

    std::cout << "  5. Verificando se a palavra 'garlgalo' foi indexada corretamente em ambos os documentos...\n";
    assert(res.found == 1);
    assert(res.documentIds.size() == 2);
    std::cout << "     -> OK: Palavra 'garlgalo' associada aos documentos 1 e 2\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: documentos indexados corretamente na arvore.\n";
    std::cout << std::string(60, '-') << "\n";
}

void run_data_tests() {
    std::cout << "\nIniciando testes do modulo 'data'...\n\n";

    test_process_words();
    test_index_documents();

    std::cout << "\nTodos os testes do modulo 'data' foram concluidos com sucesso.\n";
}
