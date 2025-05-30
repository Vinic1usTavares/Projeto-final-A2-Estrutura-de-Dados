#include "tree_utils.h"
#include <iostream>


// Função auxiliar para imprimir cada nó recursivamente
void printTreeNode(Node* node, std::string prefix, bool isLeft) {
    if (node == nullptr) return;

    std::cout << prefix;
    std::cout << (isLeft ? u8"|-- " : u8"'-- ");

    std::cout << node->word << std::endl;

    std::string childPrefix = prefix + (isLeft ? u8"|   " : u8"    ");

    printTreeNode(node->left, childPrefix, true);
    printTreeNode(node->right, childPrefix, false);
}

void printTree(BinaryTree* tree) {
    if (tree == nullptr) return; //checks if it is not a null pointer

    Node* root = tree->root;
    std::cout << tree->root->word << std::endl;


    printTreeNode(tree->root->left, "", true);
    printTreeNode(tree->root->right, "", false);

}



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

    // Criar os nós
    Node* algoritmo = criarNode("algoritmo", {2, 3, 5});
    Node* arvore    = criarNode("arvore", {1, 2});
    Node* classe    = criarNode("classe", {11});
    Node* estrutura = criarNode("estrutura", {10});
    Node* fila      = criarNode("fila", {13});
    Node* lista     = criarNode("lista", {3});
    Node* memoria   = criarNode("memoria", {4});
    Node* objeto    = criarNode("objeto", {12});
    Node* pilha     = criarNode("pilha", {14});
    Node* ponteiro  = criarNode("ponteiro", {9});
    Node* vetor     = criarNode("vetor", {7, 8});

    // Conectar os nós manualmente em ordem alfabética
    memoria->left = estrutura;
    memoria->right = ponteiro;
    estrutura->parent = memoria;
    ponteiro->parent = memoria;

    estrutura->left = classe;
    estrutura->right = lista;
    classe->parent = estrutura;
    lista->parent = estrutura;

    classe->left = algoritmo;
    classe->right = arvore;
    algoritmo->parent = classe;
    arvore->parent = classe;

    lista->right = fila;
    fila->parent = lista;

    fila->right = objeto;
    objeto->parent = fila;

    ponteiro->left = pilha;
    ponteiro->right = vetor;
    pilha->parent = ponteiro;
    vetor->parent = ponteiro;

    // Montar a árvore
    BinaryTree tree;
    tree.root = memoria;
    tree.NIL = nullptr;

    // Imprimir
    printTree(&tree);

    return 0;
}

