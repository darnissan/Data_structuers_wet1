#include "AvlTreeTemplate.h"
#include <iostream>
template <class T>
void AvlTreeTemplate<T>::deleteTree(Node *node)
{
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

template <class T>
Node *AvlTreeTemplate<T>::insert(Node *root, const T &data)
{
    if (root == nullptr)
        return new Node(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;
    root->height = getHeight(root);
    int balance = getBalance(root);
    if (balance == 2 && getBalance(root->left) >= 0) // LL rotation
        return rotateLeftLeft(root);
    if (balance == 2 && getBalance(root->left) = -1) // LR rotation
        return rotateLeftRight(root);
    if (balance == -2 && getBalance(root->right) <= 0) // RR rotation
        return rotateRightRight(root);
    if (balance == -2 && getBalance(root->right) = 1) // RL rotation
        return rotateRightLeft(root);
    return root;
}
// finding the node with the given data
template <class T>
Node *AvlTreeTemplate<T>::find(Node *node, const T &data)
{
    if (node == nullptr)
        return nullptr;
    if (data < node->data)
        return find(node->left, data);
    else if (data > node->data)
        return find(node->right, data);
    else
        return node;
}

template <class T>
Node *AvlTreeTemplate<T>::remove(Node *root, const T &data)
{
    if (root == nullptr)
        return nullptr;
    if (data < root->data)
        root->left = remove(root->left, data);
    else if (data > root->data)
        root->right = remove(root->right, data);
    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        else
        {
            Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }
    root->height = getHeight(root);
    int balance = getBalance(root);
    if (balance == 2 && getBalance(root->left) >= 0) // LL rotation
        return rotateLeftLeft(root);
    if (balance == 2 && getBalance(root->left) = -1) // LR rotation
        return rotateLeftRight(root);
    if (balance == -2 && getBalance(root->right) <= 0) // RR rotation
        return rotateRightRight(root);
    if (balance == -2 && getBalance(root->right) = 1) // RL rotation
        return rotateRightLeft(root);
    return root;
}
template <class T>
Node *AvlTreeTemplate<T>::findMin(Node *root)
{
    if (root == nullptr)
        return nullptr;
    if (root->left == nullptr)
        return root;
    return findMin(root->left);
}
template <class T>
Node *AvlTreeTemplate<T>::findMax(Node *root)
{
    if (root == nullptr)
        return nullptr;
    if (root->right == nullptr)
        return root;
    return findMax(root->right);
}
template <class T>
Node *AvlTreeTemplate<T>::rotateLeftLeft(Node *node)
{
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = getHeight(node);
    temp->height = getHeight(temp);
    return temp;
}
template <class T>
Node *AvlTreeTemplate<T>::rotateRightRight(Node *node)
{
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = getHeight(node);
    temp->height = getHeight(temp);
    return temp;
}
template <class T>
Node *AvlTreeTemplate<T>::rotateLeftRight(Node *node)
{
    node->left = rotateRightRight(node->left);
    return rotateLeftLeft(node);
}
template <class T>
Node *AvlTreeTemplate<T>::rotateRightLeft(Node *node)
{
    node->right = rotateLeftLeft(node->right);
    return rotateRightRight(node);
}
template <class T>
int AvlTreeTemplate<T>::getHeight(Node *node)
{
    if (node == nullptr)
        return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}
template <class T>
int AvlTreeTemplate<T>::getBalance(Node *node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
template <class T>
void AvlTreeTemplate<T>::printTree(Node *root)
{
    if (root == nullptr)
        return;
    printTree(root->left);
    std::cout << root->data << " ";
    printTree(root->right);
}
