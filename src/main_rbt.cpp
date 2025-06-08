#include <iostream>
#include "rbt.h"
#include "tree_utils.h"
using namespace RBT;


int main() {
    BinaryTree* tree = RBT::create();

    RBT::insert(tree, "apple", 1);
    RBT::insert(tree, "banana", 2);
    RBT::insert(tree, "apple", 3);

    printTree(tree);

    RBT::destroy(tree);
    return 0;
}
