#include "rbt.h"
#include "tree_utils.h"
#include <iostream>

int main() {
    // Cria a árvore
    BinaryTree* tree = RBT::create();

    // Insere palavras com IDs
    RBT::insert(tree, "banana", 1);
    RBT::insert(tree, "abacate", 1);
    RBT::insert(tree, "caju", 2);
    RBT::insert(tree, "damasco", 2);

    // Imprime a árvore
    printTree(tree);

    // Libera memória
    RBT::destroy(tree);

    return 0;
}
