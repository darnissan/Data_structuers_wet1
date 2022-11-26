#include "AvlTree.h"
#include "orderedTriple.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{

    AvlTree<OrderedTriple> tree;
    OrderedTriple a(1, 2, 3);
    OrderedTriple b(1, 2, 4);
    OrderedTriple c(1, 2, 5);

    tree.root = tree.Insert(tree.GetRoot(), a);
    tree.root = tree.Insert(tree.GetRoot(), b);
    tree.root = tree.Insert(tree.GetRoot(), c);
    tree.PrintInOrder(tree.GetRoot());
}