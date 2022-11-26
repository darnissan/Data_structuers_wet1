#include "AvlTree.h"
#include "orderedTriple.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
template <class T>
void printBT(const std::string &prefix, const AVLNode<T> *node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──");

        // print the value of the node
        std::cout << node->GetValue() << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "│   " : "    "), node->GetLeft(), true);
        printBT(prefix + (isLeft ? "│   " : "    "), node->GetRight(), false);
    }
}
template <class T>
void printBTs(const AVLNode<T> *node)
{
    printBT("", node, false);
}

int main()
{

    AvlTree<OrderedTriple> tree;
    OrderedTriple a(1, 2, 1);
    OrderedTriple b(1, 2, 2);
    OrderedTriple c(1, 2, 3);
    OrderedTriple d(1, 2, 4);
    OrderedTriple e(1, 2, 5);
    OrderedTriple f(1, 2, 6);
    OrderedTriple g(1, 2, 7);
    OrderedTriple h(1, 2, 8);
    OrderedTriple i(1, 2, 9);
    OrderedTriple j(1, 2, 10);
    OrderedTriple k(1, 2, 11);
    OrderedTriple m(1, 2, 12);
    OrderedTriple n(1, 2, 13);
    tree.root = tree.Insert(tree.root, a);
    tree.root = tree.Insert(tree.root, b);
    tree.root = tree.Insert(tree.root, c);
    tree.root = tree.Insert(tree.root, d);
    tree.root = tree.Insert(tree.root, e);
    tree.root = tree.Insert(tree.root, f);
    tree.root = tree.Insert(tree.root, g);
    tree.root = tree.Insert(tree.root, h);
    tree.root = tree.Insert(tree.root, i);
    tree.root = tree.Insert(tree.root, j);
    tree.root = tree.Insert(tree.root, k);
    tree.root = tree.Insert(tree.root, m);
    tree.root = tree.Insert(tree.root, n);

    tree.PrintInOrder(tree.GetRoot());
    cout << endl;
    tree.root = tree.Remove(tree.root, a);
    tree.PrintInOrder(tree.GetRoot());
    cout << endl;
    cout << f << endl;
    tree.root = tree.Remove(tree.root, f);
    tree.PrintInOrder(tree.GetRoot());
    cout << endl;
    cout << b << endl;
    tree.root = tree.Remove(tree.root, b);
    tree.PrintInOrder(tree.GetRoot());
    cout << endl;
    cout << k << endl;
    tree.root = tree.Remove(tree.root, k);
    tree.PrintInOrder(tree.GetRoot());
    cout << endl;
    printBTs(tree.GetRoot());
}