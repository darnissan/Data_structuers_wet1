#include "AvlTreeTemplate.h"
#include "orderedTriple.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{

    OrderedTriple a(1, 20, 21);
    // pointer to a node
    OrderedTriple *pointer_to_a = &a;
    AvlTreeTemplate<OrderedTriple> tree;
    tree.insert(tree.root, a);
    tree.printTree(tree.root);
}