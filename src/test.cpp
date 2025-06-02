#include "tree_utils.h"
#include <iostream>


//teste das funções
Node* criarNode(const std::string& palavra, std::vector<int> ids = {}) {
    Node* node = new Node;
    node->word = palavra;
    node->documentIds = ids;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;
    node->isRed = 0;
    return node;
}

int main() {
    std::locale::global(std::locale(""));
    // Criar os nós da árvore
    Node* algoritmo = criarNode("algoritmo", {2, 3, 5});
    Node* arvore    = criarNode("arvore", {1, 2});
    Node* memoria   = criarNode("memoria", {4});
    Node* lista     = criarNode("lista", {3});
    Node* vetor     = criarNode("vetor", {7, 8});

    // Conectar os nós
    algoritmo->left = arvore;
    algoritmo->right = memoria;
    arvore->parent = algoritmo;
    memoria->parent = algoritmo;

    memoria->left = lista;
    memoria->right = vetor;
    lista->parent = memoria;
    vetor->parent = memoria;

    // building the tree
    BinaryTree tree;
    tree.root = algoritmo;
    tree.NIL = nullptr; 

    // print Function
    printTree(&tree);

    return 0;
}