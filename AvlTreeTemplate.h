#ifndef AVL_TREE_TEMPLATE_H_
#define AVL_TREE_TEMPLATE_H_
#include <iostream>
#include "OrderedTriple.h"
struct Node
{
    OrderedTriple *data;
    Node *left;
    Node *right;
    int height;
};

template <class T>
class AvlTreeTemplate
{
public:
    AvlTreeTemplate()
    {
        this->root = nullptr;
    }
    Node *root;
    int size;
    void deleteTree(Node *node);
    Node *insert(Node *node, const T &data);
    Node *remove(Node *node, const T &data);
    Node *find(Node *node, const T &data);
    Node *findMin(Node *node);
    Node *findMax(Node *node);
    Node *rotateLeftLeft(Node *node);
    Node *rotateRightRight(Node *node);
    Node *rotateLeftRight(Node *node);
    Node *rotateRightLeft(Node *node);
    int getHeight(Node *node);
    int getBalance(Node *node);
    void printTree(Node *node);
};
#endif // AVL_TREE_TEMPLATE_H_