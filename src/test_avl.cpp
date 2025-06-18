#include <iostream>
#include <cassert>
#include "avl.h"
#include "tree_utils.h"
#include "test.h"

using namespace AVL;

void test_create_destroy_avl() {
    std::cout << "[TESTE] Criar e destruir arvore AVL...\n";

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

void test_insert_single_word_avl() {
    std::cout << "[TESTE] Insercao de uma única palavra (AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: InsertResult res = insert(tree, \"balanceada\", 1);\n";
    InsertResult res = insert(tree, "balanceada", 1);

    std::cout << "  3. Verificando se a raiz da arvore foi atualizada corretamente...\n";
    assert(tree->root != nullptr);
    assert(tree->root->word == "balanceada");
    std::cout << "     -> OK: Raiz contem a palavra 'balanceada'\n";

    std::cout << "  4. Verificando se o ID do documento foi armazenado corretamente...\n";
    assert(tree->root->documentIds.size() == 1);
    assert(tree->root->documentIds[0] == 1);
    std::cout << "     -> OK: Documento 1 registrado\n";

    std::cout << "  5. Verificando número de comparacoes retornado (res.numComparisons == 0)...\n";
    assert(res.numComparisons == 0);
    std::cout << "     -> OK: Nenhuma comparacao necessaria (arvore estava vazia)\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: insercao de palavra única verificada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_duplicate_document_avl() {
    std::cout << "[TESTE] Insercao duplicada de mesmo documento (AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"avl\", 1);\n";
    insert(tree, "avl", 1);

    std::cout << "  3. Chamando novamente: insert(tree, \"avl\", 1);\n";
    insert(tree, "avl", 1);

    std::cout << "  4. Verificando se a raiz contem a palavra correta...\n";
    assert(tree->root->word == "avl");
    std::cout << "     -> OK: Raiz contem a palavra 'avl'\n";

    std::cout << "  5. Verificando se o ID duplicado nao foi adicionado...\n";
    assert(tree->root->documentIds.size() == 1);
    std::cout << "     -> OK: Documento duplicado nao foi inserido novamente\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: duplicacao de documento corretamente evitada.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insert_same_word_different_docs_avl() {
    std::cout << "[TESTE] Insercao da mesma palavra em documentos diferentes (AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"rotacao\", 1);\n";
    insert(tree, "rotacao", 1);

    std::cout << "  3. Chamando: insert(tree, \"rotacao\", 2);\n";
    insert(tree, "rotacao", 2);

    std::cout << "  4. Verificando se a raiz contem a palavra correta...\n";
    assert(tree->root->word == "rotacao");
    std::cout << "     -> OK: Raiz contem a palavra 'rotacao'\n";

    std::cout << "  5. Verificando se ambos os IDs de documento foram armazenados...\n";
    assert(tree->root->documentIds.size() == 2);
    assert(tree->root->documentIds[0] == 1);
    assert(tree->root->documentIds[1] == 2);
    std::cout << "     -> OK: IDs 1 e 2 associados corretamente a palavra\n";

    std::cout << "  6. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: insercao da palavra em múltiplos documentos verificada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_search_found_avl() {
    std::cout << "[TESTE] Busca por palavra existente (AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"altura\", 10);\n";
    insert(tree, "altura", 10);

    std::cout << "  3. Chamando: SearchResult res = search(tree, \"altura\");\n";
    SearchResult res = search(tree, "altura");

    std::cout << "  4. Verificando se a palavra foi encontrada (res.found == 1)...\n";
    assert(res.found == 1);
    std::cout << "     -> OK: Palavra encontrada\n";

    std::cout << "  5. Verificando se o documento esta corretamente listado...\n";
    assert(res.documentIds.size() == 1);
    assert(res.documentIds[0] == 10);
    std::cout << "     -> OK: Documento 10 encontrado na lista\n";

    std::cout << "  6. Verificando número de comparacoes realizadas...\n";
    assert(res.numComparisons >= 1);
    std::cout << "     -> OK: Comparacoes realizadas: " << res.numComparisons << "\n";

    std::cout << "  7. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: busca por palavra existente validada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_search_not_found_avl() {
    std::cout << "[TESTE] Busca por palavra inexistente (AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Chamando: insert(tree, \"altura\", 10);\n";
    insert(tree, "altura", 10);

    std::cout << "  3. Chamando: SearchResult res = search(tree, \"rebalancear\");\n";
    SearchResult res = search(tree, "rebalancear");

    std::cout << "  4. Verificando se a palavra foi corretamente marcada como nao encontrada...\n";
    assert(res.found == 0);
    std::cout << "     -> OK: Palavra nao encontrada\n";

    std::cout << "  5. Verificando se a lista de documentos esta vazia...\n";
    assert(res.documentIds.empty());
    std::cout << "     -> OK: Nenhum documento associado retornado\n";

    std::cout << "  6. Verificando número de comparacoes realizadas...\n";
    assert(res.numComparisons >= 1);
    std::cout << "     -> OK: Comparacoes realizadas: " << res.numComparisons << "\n";

    std::cout << "  7. Chamando: destroy(tree);\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: busca por palavra inexistente tratada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_rotate_right_avl() {
    std::cout << "[TESTE] Rotacao simples a direita (AVL)...\n";

    std::cout << "  1. Construindo manualmente um pequeno cenario de desbalanceamento...\n";

    // Criar um no y com subarvore esquerda pesada (x)
    Node* y = createNode();
    y->word = "c";

    Node* x = createNode();
    x->word = "b";

    Node* a = createNode();
    a->word = "a";

    // Construir a estrutura: y -> x -> a
    y->left = x;
    x->left = a;

    // Atualizar alturas manualmente
    a->height = 1;
    x->height = 2;
    y->height = 3;

    std::cout << "     -> Estrutura inicial montada:\n";
    std::cout << "        y = 'c', y->left = 'b', b->left = 'a'\n";

    std::cout << "  2. Chamando: rotateRight(y);\n";
    int rotationsCount = 0;
    Node* newRoot = rotateRight(y, rotationsCount);

    std::cout << "  3. Verificando se a nova raiz e 'b'...\n";
    assert(newRoot->word == "b");
    std::cout << "     -> OK: Nova raiz e 'b'\n";

    std::cout << "  4. Verificando filhos da nova raiz...\n";
    assert(newRoot->left == a);
    assert(newRoot->right == y);
    std::cout << "     -> OK: Estrutura da arvore correta apos rotacao\n";

    std::cout << "  5. Verificando se alturas foram atualizadas corretamente...\n";
    assert(a->height == 1);
    assert(y->height == 1);
    assert(newRoot->height == 2);
    std::cout << "     -> OK: Alturas consistentes\n";

    std::cout << "  6. Limpando memoria manualmente...\n";
    destroyNode(newRoot);  // isso ja libera todos os nos recursivamente

    std::cout << "Teste concluido com sucesso: rotacao simples a direita validada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_rotate_left_avl() {
    std::cout << "[TESTE] Rotacao simples a esquerda (AVL)...\n";

    std::cout << "  1. Construindo manualmente um pequeno cenario de desbalanceamento...\n";

    // Criar um no x com subarvore direita pesada (y)
    Node* x = createNode();
    x->word = "a";

    Node* y = createNode();
    y->word = "b";

    Node* z = createNode();
    z->word = "c";

    // Construir a estrutura: x -> y -> z
    x->right = y;
    y->right = z;

    // Atualizar alturas manualmente
    z->height = 1;
    y->height = 2;
    x->height = 3;

    std::cout << "     -> Estrutura inicial montada:\n";
    std::cout << "        x = 'a', x->right = 'b', b->right = 'c'\n";

    std::cout << "  2. Chamando: rotateLeft(x);\n";
    int rotationsCount = 0;
    Node* newRoot = rotateLeft(x, rotationsCount);

    std::cout << "  3. Verificando se a nova raiz e 'b'...\n";
    assert(newRoot->word == "b");
    std::cout << "     -> OK: Nova raiz e 'b'\n";

    std::cout << "  4. Verificando filhos da nova raiz...\n";
    assert(newRoot->left == x);
    assert(newRoot->right == z);
    std::cout << "     -> OK: Estrutura da arvore correta apos rotacao\n";

    std::cout << "  5. Verificando se alturas foram atualizadas corretamente...\n";
    assert(x->height == 1);
    assert(z->height == 1);
    assert(newRoot->height == 2);
    std::cout << "     -> OK: Alturas consistentes\n";

    std::cout << "  6. Limpando memoria manualmente...\n";
    destroyNode(newRoot);  // isso ja libera todos os nos recursivamente

    std::cout << "Teste concluido com sucesso: rotacao simples a esquerda validada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_balance_factor_avl() {
    std::cout << "[TESTE] Calculo do fator de balanceamento (AVL)...\n";

    std::cout << "  1. Construindo manualmente uma arvore com fator de balanceamento conhecido...\n";

    // Criar um no root
    Node* root = createNode();
    root->word = "b";

    // Criar filhos
    Node* left = createNode();
    left->word = "a";

    Node* right = createNode();
    right->word = "c";

    // Construir a estrutura: root com filhos esquerdo e direito
    root->left = left;
    root->right = right;

    // Definir alturas manualmente
    left->height = 2;
    right->height = 1;
    root->height = 3;

    std::cout << "     -> Estrutura inicial montada:\n";
    std::cout << "        root = 'b', left = 'a' (height = 2), right = 'c' (height = 1)\n";

    std::cout << "  2. Chamando: balanceFactor(root);\n";
    int bf = balanceFactor(root);

    std::cout << "  3. Verificando se o fator de balanceamento e correto (esperado: 1)...\n";
    assert(bf == 1);
    std::cout << "     -> OK: Fator de balanceamento e 1\n";

    std::cout << "  4. Limpando memoria manualmente...\n";
    destroyNode(root);  // isso libera root e recursivamente left e right

    std::cout << "Teste concluido com sucesso: calculo do fator de balanceamento validado corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_height_avl() {
    std::cout << "[TESTE] Calculo da altura do no (AVL)...\n";

    std::cout << "  1. Construindo manualmente uma arvore pequena com alturas conhecidas...\n";

    // Criar nos
    Node* root = createNode();
    root->word = "m";

    Node* left = createNode();
    left->word = "f";

    Node* right = createNode();
    right->word = "t";

    Node* left_left = createNode();
    left_left->word = "b";

    // Construir a estrutura:
    root->left = left;
    root->right = right;
    left->left = left_left;

    // Definir alturas manualmente
    left_left->height = 1;
    left->height = 2;
    right->height = 1;
    root->height = 3;

    std::cout << "     -> Estrutura inicial montada:\n";
    std::cout << "        root = 'm', left = 'f', right = 't', left->left = 'b'\n";

    std::cout << "  2. Chamando: height(root);\n";
    int h_root = height(root);
    std::cout << "  3. Verificando altura da raiz (esperado: 3)...\n";
    assert(h_root == 3);
    std::cout << "     -> OK: Altura da raiz e 3\n";

    std::cout << "  4. Chamando: height(left);\n";
    int h_left = height(left);
    std::cout << "  5. Verificando altura do no 'f' (esperado: 2)...\n";
    assert(h_left == 2);
    std::cout << "     -> OK: Altura do no 'f' e 2\n";

    std::cout << "  6. Chamando: height(right);\n";
    int h_right = height(right);
    std::cout << "  7. Verificando altura do no 't' (esperado: 1)...\n";
    assert(h_right == 1);
    std::cout << "     -> OK: Altura do no 't' e 1\n";

    std::cout << "  8. Chamando: height(left_left);\n";
    int h_left_left = height(left_left);
    std::cout << "  9. Verificando altura do no 'b' (esperado: 1)...\n";
    assert(h_left_left == 1);
    std::cout << "     -> OK: Altura do no 'b' e 1\n";

    std::cout << " 10. Chamando: height(nullptr);\n";
    int h_null = height(nullptr);
    std::cout << " 11. Verificando altura de no nulo (esperado: 0)...\n";
    assert(h_null == 0);
    std::cout << "     -> OK: Altura de no nulo e 0\n";

    std::cout << " 12. Limpando memoria manualmente...\n";
    destroyNode(root);  // libera todos os nos recursivamente

    std::cout << "Teste concluido com sucesso: calculo de altura validado corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_max_avl() {
    std::cout << "[TESTE] Funcao auxiliar max(a, b) (AVL)...\n";

    std::cout << "  1. Chamando: max(3, 5);\n";
    int result1 = max(3, 5);
    std::cout << "  2. Verificando se o resultado e 5...\n";
    assert(result1 == 5);
    std::cout << "     -> OK: max(3, 5) == 5\n";

    std::cout << "  3. Chamando: max(10, -4);\n";
    int result2 = max(10, -4);
    std::cout << "  4. Verificando se o resultado e 10...\n";
    assert(result2 == 10);
    std::cout << "     -> OK: max(10, -4) == 10\n";

    std::cout << "  5. Chamando: max(-7, -2);\n";
    int result3 = max(-7, -2);
    std::cout << "  6. Verificando se o resultado e -2...\n";
    assert(result3 == -2);
    std::cout << "     -> OK: max(-7, -2) == -2\n";

    std::cout << "  7. Chamando: max(0, 0);\n";
    int result4 = max(0, 0);
    std::cout << "  8. Verificando se o resultado e 0...\n";
    assert(result4 == 0);
    std::cout << "     -> OK: max(0, 0) == 0\n";

    std::cout << "Teste concluido com sucesso: funcao max(a, b) validada corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insertAux_balance_left_left_case() {
    std::cout << "[TESTE] Insercao com balanceamento (caso esquerda-esquerda, AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Inserindo palavras em ordem decrescente: 'c', 'b', 'a'\n";

    std::cout << "     -> Inserindo 'c'...\n";
    insert(tree, "c", 1);

    std::cout << "     -> Inserindo 'b'...\n";
    insert(tree, "b", 1);

    std::cout << "     -> Inserindo 'a' (deve forcar rotacao simples a direita)...\n";
    insert(tree, "a", 1);

    std::cout << "  3. Verificando se a raiz da arvore foi atualizada corretamente (esperado: 'b')...\n";
    assert(tree->root != nullptr);
    assert(tree->root->word == "b");
    std::cout << "     -> OK: Nova raiz e 'b'\n";

    std::cout << "  4. Verificando filhos da nova raiz...\n";
    assert(tree->root->left != nullptr);
    assert(tree->root->left->word == "a");

    assert(tree->root->right != nullptr);
    assert(tree->root->right->word == "c");

    std::cout << "     -> OK: Estrutura da arvore apos balanceamento e correta ('a' a esquerda, 'c' a direita)\n";

    std::cout << "  5. Limpando memoria manualmente...\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: caso esquerda-esquerda validado corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insertAux_balance_left_right_case() {
    std::cout << "[TESTE] Insercao com balanceamento (caso esquerda-direita, AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Inserindo palavras em ordem: 'c', 'a', 'b'\n";

    std::cout << "     -> Inserindo 'c'...\n";
    insert(tree, "c", 1);

    std::cout << "     -> Inserindo 'a'...\n";
    insert(tree, "a", 1);

    std::cout << "     -> Inserindo 'b' (deve forcar rotacao dupla esquerda-direita)...\n";
    insert(tree, "b", 1);

    std::cout << "  3. Verificando se a raiz da arvore foi atualizada corretamente (esperado: 'b')...\n";
    assert(tree->root != nullptr);
    assert(tree->root->word == "b");
    std::cout << "     -> OK: Nova raiz e 'b'\n";

    std::cout << "  4. Verificando filhos da nova raiz...\n";
    assert(tree->root->left != nullptr);
    assert(tree->root->left->word == "a");

    assert(tree->root->right != nullptr);
    assert(tree->root->right->word == "c");

    std::cout << "     -> OK: Estrutura da arvore apos balanceamento e correta ('a' a esquerda, 'c' a direita)\n";

    std::cout << "  5. Limpando memoria manualmente...\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: caso esquerda-direita validado corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void test_insertAux_balance_right_left_case() {
    std::cout << "[TESTE] Insercao com balanceamento (caso direita-esquerda, AVL)...\n";

    std::cout << "  1. Chamando: BinaryTree* tree = create();\n";
    BinaryTree* tree = create();

    std::cout << "  2. Inserindo palavras em ordem: 'a', 'c', 'b'\n";

    std::cout << "     -> Inserindo 'a'...\n";
    insert(tree, "a", 1);

    std::cout << "     -> Inserindo 'c'...\n";
    insert(tree, "c", 1);

    std::cout << "     -> Inserindo 'b' (deve forcar rotacao dupla direita-esquerda)...\n";
    insert(tree, "b", 1);

    std::cout << "  3. Verificando se a raiz da arvore foi atualizada corretamente (esperado: 'b')...\n";
    assert(tree->root != nullptr);
    assert(tree->root->word == "b");
    std::cout << "     -> OK: Nova raiz e 'b'\n";

    std::cout << "  4. Verificando filhos da nova raiz...\n";
    assert(tree->root->left != nullptr);
    assert(tree->root->left->word == "a");

    assert(tree->root->right != nullptr);
    assert(tree->root->right->word == "c");

    std::cout << "     -> OK: Estrutura da arvore apos balanceamento e correta ('a' a esquerda, 'c' a direita)\n";

    std::cout << "  5. Limpando memoria manualmente...\n";
    destroy(tree);

    std::cout << "Teste concluido com sucesso: caso direita-esquerda validado corretamente.\n";
    std::cout << std::string(60, '-') << "\n";
}

void run_avl_tests() {
    std::cout << "\nIniciando testes da arvore AVL...\n\n";

    test_create_destroy_avl();
    test_insert_single_word_avl();
    test_insert_duplicate_document_avl();
    test_insert_same_word_different_docs_avl();
    test_search_found_avl();
    test_search_not_found_avl();
    test_max_avl();
    test_rotate_right_avl();
    test_rotate_left_avl();
    test_balance_factor_avl();
    test_height_avl();
    test_insertAux_balance_left_left_case();
    test_insertAux_balance_left_right_case();
    test_insertAux_balance_right_left_case();

    std::cout << "\nTodos os testes da AVL foram concluidos com sucesso.\n";
}
