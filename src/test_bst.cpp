#include <iostream>
#include <cassert>
#include "bst.h"
#include "tree_utils.h"
#include "test.h"

using namespace BST;

void test_create_destroy() {
    std::cout << "[TESTE] Criar e destruir arvore binaria...\n";
    
    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();
    std::cout << "     -> Ponteiro retornado: " << tree << "\n";

    std::cout << "  2. Verificando se a arvore foi criada corretamente (tree != nullptr)...\n";
    assert(tree != nullptr);
    std::cout << "     -> OK: Ponteiro nao e nulo\n";

    std::cout << "  3. Verificando se a raiz da arvore esta vazia (tree->root == nullptr)...\n";
    assert(tree->root == nullptr);
    std::cout << "     -> OK: Raiz da arvore e nula\n";

    std::cout << "  4. Chamando: destroy(tree);\n";
    destroy(tree);
    std::cout << "     -> OK: Memoria liberada com sucesso\n";

    std::cout << "Teste concluido com sucesso: criacao e destruicao funcionam corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_single_word() {
    std::cout << "[TESTE] Insercao de uma unica palavra...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: InsertResult res = insert(tree, \"algoritmo\", 1);\n";
    InsertResult res = insert(tree, "algoritmo", 1);

    std::cout << "  3. Verificando se a raiz da arvore foi atualizada corretamente...\n";
    assert(tree->root != nullptr);
    assert(tree->root->word == "algoritmo");
    std::cout << "     -> OK: Raiz contem a palavra 'algoritmo'\n";

    std::cout << "  4. Verificando se o ID do documento foi armazenado corretamente...\n";
    assert(tree->root->documentIds.size() == 1);
    assert(tree->root->documentIds[0] == 1);
    std::cout << "     -> OK: Documento 1 registrado\n";

    std::cout << "  5. Verificando numero de comparacoes retornado (res.numComparisons == 0)...\n";
    assert(res.numComparisons == 0);
    std::cout << "     -> OK: Nenhuma comparacao necessaria (arvore estava vazia)\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: insercao de palavra unica verificada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_duplicate_document() {
    std::cout << "[TESTE] Insercao duplicada de mesmo documento...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"estrutura\", 1);\n";
    insert(tree, "estrutura", 1);

    std::cout << "  3. Chamando novamente: insert(tree, \"estrutura\", 1);\n";
    insert(tree, "estrutura", 1);

    std::cout << "  4. Verificando se a raiz contem a palavra correta...\n";
    assert(tree->root->word == "estrutura");

    std::cout << "  5. Verificando se o ID duplicado nao foi adicionado...\n";
    assert(tree->root->documentIds.size() == 1);
    std::cout << "     -> OK: Documento duplicado nao foi inserido novamente\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: duplicacao de documento corretamente evitada.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_same_word_different_docs() {
    std::cout << "[TESTE] Insercao da mesma palavra em documentos diferentes...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"ponteiro\", 1);\n";
    insert(tree, "ponteiro", 1);

    std::cout << "  3. Chamando: insert(tree, \"ponteiro\", 2);\n";
    insert(tree, "ponteiro", 2);

    std::cout << "  4. Verificando se a raiz contem a palavra correta...\n";
    assert(tree->root->word == "ponteiro");

    std::cout << "  5. Verificando se ambos os IDs de documento foram armazenados...\n";
    assert(tree->root->documentIds.size() == 2);
    assert(tree->root->documentIds[0] == 1);
    assert(tree->root->documentIds[1] == 2);
    std::cout << "     -> OK: IDs 1 e 2 associados corretamente a palavra\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: insercao da palavra em multiplos documentos verificada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_search_found() {
    std::cout << "[TESTE] Busca por palavra existente...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"hash\", 10);\n";
    insert(tree, "hash", 10);

    std::cout << "  3. Chamando: SearchResult res = search(tree, \"hash\");\n";
    SearchResult res = ::search(tree, "hash");

    std::cout << "  4. Verificando se a palavra foi encontrada (res.found == 1)...\n";
    assert(res.found == 1);

    std::cout << "  5. Verificando se o documento esta corretamente listado...\n";
    assert(res.documentIds.size() == 1);
    assert(res.documentIds[0] == 10);
    std::cout << "     -> OK: Documento 10 encontrado na lista\n";

    std::cout << "  6. Verificando numero de comparacoes realizadas...\n";
    assert(res.numComparisons >= 1);
    std::cout << "     -> OK: Comparacoes realizadas: " << res.numComparisons << "\n";

    std::cout << "  7. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: busca por palavra existente validada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_search_not_found() {
    std::cout << "[TESTE] Busca por palavra inexistente...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"memoria\", 5);\n";
    insert(tree, "memoria", 5);

    std::cout << "  3. Chamando: SearchResult res = search(tree, \"vetor\");\n";
    SearchResult res = search(tree, "vetor");

    std::cout << "  4. Verificando se a palavra foi corretamente marcada como nao encontrada...\n";
    assert(res.found == 0);
    std::cout << "     -> OK: Palavra nao encontrada\n";

    std::cout << "  5. Verificando se a lista de documentos esta vazia...\n";
    assert(res.documentIds.empty());
    std::cout << "     -> OK: Nenhum documento associado retornado\n";

    std::cout << "  6. Verificando numero de comparacoes realizadas...\n";
    assert(res.numComparisons >= 1);
    std::cout << "     -> OK: Comparacoes realizadas: " << res.numComparisons << "\n";

    std::cout << "  7. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: busca por palavra inexistente tratada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void run_bst_tests() {
    std::cout << "\nIniciando testes da arvore Binaria de Busca (BST)...\n\n";

    test_create_destroy();
    test_insert_single_word();
    test_insert_duplicate_document();
    test_insert_same_word_different_docs();
    test_search_found();
    test_search_not_found();

    std::cout << "\nTodos os testes da BST foram concluidos com sucesso.\n";
}
