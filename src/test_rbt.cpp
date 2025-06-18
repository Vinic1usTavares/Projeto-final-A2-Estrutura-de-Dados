#include <iostream>
#include <cassert>
#include "rbt.h"         
#include "tree_utils.h"  
#include "test.h" 
#include <functional>       


using namespace RBT;    

void test_create_destroy() {
    std::cout << "[TESTE] Criar e destruir árvore rubro-negra...\n";
    
    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();
    std::cout << "     -> Ponteiro retornado: " << tree << "\n";

    std::cout << "  2. Verificando se a árvore foi criada corretamente (tree != nullptr)...\n";
    assert(tree != nullptr);
    std::cout << "     -> OK: Ponteiro não é nulo\n";

    std::cout << "  3. Verificando se a raiz da árvore está vazia (tree->root == tree->NIL)...\n";
    assert(tree->root == tree->NIL);
    std::cout << "     -> OK: Raiz da árvore é NIL\n";

    std::cout << "  4. Chamando: destroy(tree);\n";
    destroy(tree);
    std::cout << "     -> OK: Memória liberada com sucesso\n";

    std::cout << "Teste concluído com sucesso: criação e destruição funcionam corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_single_word() {
    std::cout << "[TESTE] Inserção de uma única palavra...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: InsertResult res = insert(tree, \"algoritmo\", 1);\n";
    InsertResult res = insert(tree, "algoritmo", 1);

    std::cout << "  3. Verificando se a raiz da árvore foi atualizada corretamente...\n";
    assert(tree->root != tree->NIL);
    assert(tree->root->word == "algoritmo");
    std::cout << "     -> OK: Raiz contém a palavra 'algoritmo'\n";

    std::cout << "  4. Verificando se o ID do documento foi armazenado corretamente...\n";
    assert(tree->root->documentIds.size() == 1);
    assert(tree->root->documentIds[0] == 1);
    std::cout << "     -> OK: Documento 1 registrado\n";

    std::cout << "  5. Verificando número de comparações retornado (res.numComparisons == 0)...\n";
    assert(res.numComparisons == 0);
    std::cout << "     -> OK: Nenhuma comparação necessária (árvore estava vazia)\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluído com sucesso: inserção de palavra única verificada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_duplicate_document() {
    std::cout << "[TESTE] Inserção duplicada de mesmo documento...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"estrutura\", 1);\n";
    insert(tree, "estrutura", 1);

    std::cout << "  3. Chamando novamente: insert(tree, \"estrutura\", 1);\n";
    insert(tree, "estrutura", 1);

    std::cout << "  4. Verificando se a raiz contém a palavra correta...\n";
    assert(tree->root->word == "estrutura");

    std::cout << "  5. Verificando se o ID duplicado não foi adicionado...\n";
    assert(tree->root->documentIds.size() == 1);
    std::cout << "     -> OK: Documento duplicado não foi inserido novamente\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluído com sucesso: duplicação de documento corretamente evitada.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_same_word_different_docs() {
    std::cout << "[TESTE] Inserção da mesma palavra em documentos diferentes...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"ponteiro\", 1);\n";
    insert(tree, "ponteiro", 1);

    std::cout << "  3. Chamando: insert(tree, \"ponteiro\", 2);\n";
    insert(tree, "ponteiro", 2);

    std::cout << "  4. Verificando se a raiz contém a palavra correta...\n";
    assert(tree->root->word == "ponteiro");

    std::cout << "  5. Verificando se ambos os IDs de documento foram armazenados...\n";
    assert(tree->root->documentIds.size() == 2);
    assert(tree->root->documentIds[0] == 1);
    assert(tree->root->documentIds[1] == 2);
    std::cout << "     -> OK: IDs 1 e 2 associados corretamente à palavra\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluído com sucesso: inserção da palavra em múltiplos documentos verificada corretamente.\n";
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

    std::cout << "  5. Verificando se o documento está corretamente listado...\n";
    assert(res.documentIds.size() == 1);
    assert(res.documentIds[0] == 10);
    std::cout << "     -> OK: Documento 10 encontrado na lista\n";

    std::cout << "  6. Verificando número de comparações realizadas...\n";
    assert(res.numComparisons >= 1);
    std::cout << "     -> OK: Comparações realizadas: " << res.numComparisons << "\n";

    std::cout << "  7. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluído com sucesso: busca por palavra existente validada corretamente.\n";
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

    std::cout << "  4. Verificando se a palavra foi corretamente marcada como não encontrada...\n";
    assert(res.found == 0);
    std::cout << "     -> OK: Palavra não encontrada\n";

    std::cout << "  5. Verificando se a lista de documentos está vazia...\n";
    assert(res.documentIds.empty());
    std::cout << "     -> OK: Nenhum documento associado retornado\n";

    std::cout << "  6. Verificando número de comparações realizadas...\n";
    assert(res.numComparisons >= 1);
    std::cout << "     -> OK: Comparações realizadas: " << res.numComparisons << "\n";

    std::cout << "  7. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluído com sucesso: busca por palavra inexistente tratada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_rbt_properties_after_inserts() {
    std::cout << "[TESTE] Propriedades fundamentais da Árvore Rubro-Negra após múltiplas inserções...\n";
    BinaryTree* tree = create();

    std::vector<std::string> palavras = {"delta", "alpha", "epsilon", "beta", "gamma", "zeta", "eta", "theta"};
    int docId = 1;
    for (const auto& palavra : palavras) {
        insert(tree, palavra, docId++);
    }

    std::cout << "Verificando se a raiz da árvore é preta...\n";
    assert(tree->root->isRed == false);
    std::cout << "✓ A raiz é preta.\n";

    std::cout << "Verificando se nenhum nó vermelho tem filho vermelho...\n";
    bool noRedRedViolations = checkRedProperty(tree->root, tree->NIL);
    assert(noRedRedViolations);
    std::cout << "✓ Nenhum nó vermelho possui filho vermelho (regra RBT preservada).\n";

    std::cout << "Verificando se a black-height (altura preta) das subárvores esquerda e direita da raiz são iguais...\n";
    int blackHeightLeft = blackHeight(tree->root->left, tree->NIL);
    int blackHeightRight = blackHeight(tree->root->right, tree->NIL);
    assert(blackHeightLeft == blackHeightRight);
    std::cout << "✓ As black-heights esquerda e direita da raiz são iguais: " 
              << blackHeightLeft << "\n";

    destroy(tree);
    std::cout << "✓ Teste concluído com sucesso: propriedades da RBT mantidas após múltiplas inserções.\n";
    std::cout << std::string(60, '-') << "\n";
}


void test_black_height_consistency() {
    std::cout << "[TESTE] Consistência da altura preta (black-height) em todos os nós da árvore...\n";
    BinaryTree* tree = create();

    std::vector<std::string> palavras = {"m", "b", "r", "a", "c", "z", "n"};
    int docId = 1;
    for (const auto& palavra : palavras) {
        insert(tree, palavra, docId++);
    }

    std::cout << "Percorrendo todos os nós para verificar se a black-height das subárvores esquerda e direita é igual...\n";
    std::function<void(Node*)> checkBlackHeightRecursive = [&](Node* node) {
        if (node == tree->NIL) return;
        int leftBH = blackHeight(node->left, tree->NIL);
        int rightBH = blackHeight(node->right, tree->NIL);
        if (leftBH == rightBH) {
            std::cout << "Propriedade black-height conferida!\n";
        };
        assert(leftBH == rightBH);
        checkBlackHeightRecursive(node->left);
        checkBlackHeightRecursive(node->right);
    };

    checkBlackHeightRecursive(tree->root);

    destroy(tree);
    std::cout << "✓ Teste concluído com sucesso: todos os nós possuem black-heights consistentes.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_rbt_max_min_path_ratio() {
    std::cout << "[TESTE] Verificação do limite entre caminho mais longo e mais curto na RBT...\n";
    BinaryTree* tree = create();

    std::vector<std::string> palavras = {
        "Era", "uma", "vez", "um", "coelhinho", "chamado", "Tico", 
        "que", "adorava", "brincar", "no", "bosque", "com", "seus", "amigos",
        "Certo", "dia", "ele", "encontrou", "uma", "chave", "mágica",
        "debaixo", "de", "uma", "pedra", "brilhante"
    };

    int docId = 1;
    for (const auto& palavra : palavras) {
        insert(tree, palavra, docId++);
    }

    int altura = GetHeight(tree->root); // maior caminho (pode contar todos os nós)
    int minPath = findMinPath(tree, tree->root); // menor caminho até folha (todos os nós)

    std::cout << "  -> Altura da árvore (maior caminho): " << altura << "\n";
    std::cout << "  -> Menor caminho até uma folha:       " << minPath << "\n";
    std::cout << "  -> Relação altura / menor caminho:    " << (double)altura / minPath << "\n";

    // ASSERT: o maior caminho é no máximo o dobro do menor caminho
    assert(altura <= 2 * minPath);


    destroy(tree);
    std::cout << "Teste concluído com sucesso: proporção entre maior e menor caminho está dentro do limite da RBT.\n";
    std::cout << std::string(60, '-') << "\n";
}


void run_rbt_tests() {

    std::cout << "\nIniciando testes da Árvore Rubro-Negra (RBT)...\n\n";

    test_create_destroy();
    test_insert_single_word();
    test_insert_duplicate_document();
    test_insert_same_word_different_docs();
    test_search_found();
    test_search_not_found();

    // Novos testes rbt
    test_rbt_properties_after_inserts();
    test_black_height_consistency();
    test_rbt_max_min_path_ratio();

    std::cout << "\nTodos os testes da RBT foram concluídos com sucesso.\n";
}
