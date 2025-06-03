#include <iostream>
#include <cassert>
#include "bst.h"
#include "tree_utils.h"
#include "test.h"

using namespace BST;

void test_create_destroy() {
    std::cout << "[TESTE] Criar e destruir árvore...\n";
    BinaryTree* tree = create();
    assert(tree != nullptr);
    assert(tree->root == nullptr);
    destroy(tree);
    std::cout << "  -> OK: Árvore criada e destruída corretamente\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_single_word() {
    std::cout << "[TESTE] Inserção de uma única palavra...\n";
    BinaryTree* tree = create();
    InsertResult res = insert(tree, "algoritmo", 1);
    assert(tree->root != nullptr);
    assert(tree->root->word == "algoritmo");
    assert(tree->root->documentIds.size() == 1);
    assert(tree->root->documentIds[0] == 1);
    assert(res.numComparisons == 0);
    destroy(tree);
    std::cout << "  -> OK: Palavra única inserida corretamente\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_duplicate_document() {
    std::cout << "[TESTE] Inserção duplicada de mesmo documento...\n";
    BinaryTree* tree = create();
    insert(tree, "estrutura", 1);
    insert(tree, "estrutura", 1);
    assert(tree->root->word == "estrutura");
    assert(tree->root->documentIds.size() == 1);
    destroy(tree);
    std::cout << "  -> OK: Documento duplicado não foi adicionado\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_same_word_different_docs() {
    std::cout << "[TESTE] Inserção da mesma palavra em documentos diferentes...\n";
    BinaryTree* tree = create();
    insert(tree, "ponteiro", 1);
    insert(tree, "ponteiro", 2);
    assert(tree->root->word == "ponteiro");
    assert(tree->root->documentIds.size() == 2);
    assert(tree->root->documentIds[0] == 1);
    assert(tree->root->documentIds[1] == 2);
    destroy(tree);
    std::cout << "  -> OK: Palavra associada a múltiplos documentos\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_search_found() {
    std::cout << "[TESTE] Busca por palavra existente...\n";
    BinaryTree* tree = create();
    insert(tree, "hash", 10);
    SearchResult res = search(tree, "hash");
    assert(res.found == 1);
    assert(res.documentIds.size() == 1);
    assert(res.documentIds[0] == 10);
    assert(res.numComparisons >= 1);
    destroy(tree);
    std::cout << "  -> OK: Palavra encontrada com sucesso\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_search_not_found() {
    std::cout << "[TESTE] Busca por palavra inexistente...\n";
    BinaryTree* tree = create();
    insert(tree, "memoria", 5);
    SearchResult res = search(tree, "vetor");
    assert(res.found == 0);
    assert(res.documentIds.empty());
    assert(res.numComparisons >= 1);
    destroy(tree);
    std::cout << "  -> OK: Palavra não encontrada\n";
    std::cout << std::string(60, '-') << "\n";
}

void run_bst_tests() {
    std::cout << "\nIniciando testes da Árvore Binária de Busca (BST)...\n\n";

    test_create_destroy();
    test_insert_single_word();
    test_insert_duplicate_document();
    test_insert_same_word_different_docs();
    test_search_found();
    test_search_not_found();

    std::cout << "\nTodos os testes da BST foram concluídos com sucesso.\n";
}
