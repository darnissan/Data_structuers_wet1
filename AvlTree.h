#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>

template <class T>
class AVLNode
{
public:
    AVLNode(const T &value) : data(value), left(NULL), right(NULL) {}
    ~AVLNode() {}

    const T &GetValue() const { return data; }
    void SetLeft(AVLNode *node) { left = node; }
    AVLNode *GetLeft() const { return left; }
    void SetRight(AVLNode *node) { right = node; }
    AVLNode *GetRight() const { return right; }

    void Print() const { std::cout << data << std::endl; }

private:
    AVLNode();

    T data;
    AVLNode *left;
    AVLNode *right;
    int height;
};

template <class T>
class AvlTree
{
public:
    AVLNode<T> *root;
    AvlTree() : root(NULL) {}
    ~AvlTree();

    AVLNode<T> *GetRoot() const { return root; }
    AVLNode<T> *find(AVLNode<T> *root, const T &value) const;
    int height(AVLNode<T> *root) const;
    int GetBF(AVLNode<T> *root) const;
    AVLNode<T> *RotateLL(AVLNode<T> *root);
    AVLNode<T> *RotateRR(AVLNode<T> *root);
    AVLNode<T> *RotateLR(AVLNode<T> *root);
    AVLNode<T> *RotateRL(AVLNode<T> *root);

    AVLNode<T> *Insert(AVLNode<T> *root, const T &value);
    AVLNode<T> *Remove(const T &value);
    void PrintInOrder(AVLNode<T> *root) const;

private:
    void DeleteAvlNode(AVLNode<T> *nodeToRemove); // function used by the destructor
};
template <class T>
AvlTree<T>::~AvlTree()
{
    if (root)
    {
        DeleteAvlNode(root);
    }
}
template <class T>
void AvlTree<T>::DeleteAvlNode(AVLNode<T> *nodeToRemove)
{
    if (nodeToRemove)
    {
        DeleteAvlNode(nodeToRemove->GetLeft());
        DeleteAvlNode(nodeToRemove->GetRight());
        delete nodeToRemove;
    }
}
template <class T>
AVLNode<T> *AvlTree<T>::find(AVLNode<T> *root, const T &value) const
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->GetValue() == value)
    {
        return root;
    }
    if (root->GetValue() > value)
    {
        return find(root->GetLeft(), value);
    }
    else
    {
        return find(root->GetRight(), value);
    }
}
template <class T>
int AvlTree<T>::height(AVLNode<T> *root) const
{
    int Ownheight = 0;
    if (root == NULL)
    {
        return 0;
    }
    int leftHeight = height(root->GetLeft());
    int rightHeight = height(root->GetRight());
    Ownheight = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    return Ownheight;
}
template <class T>
int AvlTree<T>::GetBF(AVLNode<T> *root) const
{
    int leftHeight = height(root->GetLeft());
    int rightHeight = height(root->GetRight());
    int balanceFactor = leftHeight - rightHeight;
    return balanceFactor;
}
template <class T>
AVLNode<T> *AvlTree<T>::RotateLL(AVLNode<T> *node)
{
    AVLNode<T> *temp = node->GetLeft();
    node->SetLeft(temp->GetRight());
    temp->SetRight(node);
    node = temp;
    return node;
}
template <class T>
AVLNode<T> *AvlTree<T>::RotateRR(AVLNode<T> *node)
{
    AVLNode<T> *temp = node->GetRight();
    node->SetRight(temp->GetLeft());
    temp->SetLeft(node);
    node = temp;
    return node;
}
template <class T>
AVLNode<T> *AvlTree<T>::RotateLR(AVLNode<T> *node)
{
    RotateRR(node->GetLeft());
    RotateLL(node);
    return node;
}
template <class T>
AVLNode<T> *AvlTree<T>::RotateRL(AVLNode<T> *node)
{
    RotateLL(node->GetRight());
    RotateRR(node);
    return node;
}
template <class T>
AVLNode<T> *AvlTree<T>::Insert(AVLNode<T> *node, const T &value)
{
    if (this->root == NULL)
    {
        this->root = new AVLNode<T>(value);
        return this->root;
    }
    if (node == NULL) // meaning we've reached a leaf and we can insert the new node
    {
        node = new AVLNode<T>(value);
        return node;
    }
    if (node->GetValue() > value)
    {
        node->SetLeft(Insert(node->GetLeft(), value));
    }
    else if (node->GetValue() < value)
    {
        node->SetRight(Insert(node->GetRight(), value));
    }
    else
    {
        return node;
    }
    int balanceFactor = GetBF(node);
    if (balanceFactor == 2 && GetBF(node->GetLeft()) >= 0)
    {
        node = RotateLL(node);
    }
    else if (balanceFactor == 2 && GetBF(node->GetLeft()) == -1)
    {
        node = RotateLR(node);
    }
    else if (balanceFactor == -2 && GetBF(node->GetRight()) <= 0)
    {
        node = RotateRR(node);
    }
    else if (balanceFactor == -2 && GetBF(node->GetRight()) == 1)
    {
        node = RotateRL(node);
    }
    return node;
}
template <class T>
AVLNode<T> *AvlTree<T>::Remove(const T &value)
{
    if (root == NULL)
    {
        return root;
    }
    if (value < root->GetValue())
    {
        root->GetLeft() = Remove(root->GetLeft(), value);
    }
    else if (value > root->GetValue())
    {
        root->GetRight() = Remove(root->GetRight(), value);
    }
    else
    {
        if (root->GetLeft() == NULL)
        {
            AVLNode<T> *temp = root->GetRight();
            delete root;
            return temp;
        }
        else if (root->GetRight() == NULL)
        {
            AVLNode<T> *temp = root->GetLeft();
            delete root;
            return temp;
        }
        AVLNode<T> *temp = root->GetRight();
        while (temp->GetLeft() != NULL)
        {
            temp = temp->GetLeft();
        }
        root->SetValue(temp->GetValue());
        root->GetRight() = Remove(root->GetRight(), temp->GetValue());
    }
    int balanceFactor = GetBF(root);
    if (balanceFactor == 2 && GetBF(root.GetLeft()) >= 0)
    {
        RotateLL(root);
    }
    else if (balanceFactor == 2 && GetBF(root.GetLeft()) == -1)
    {
        RotateLR(root);
    }
    else if (balanceFactor == -2 && GetBF(root.GetRight()) <= -1)
    {
        RotateRR(root);
    }
    else if (balanceFactor == -2 && GetBF(root.GetRight()) == 1)
    {
        RotateRL(root);
    }
    return root;
}
template <class T>
void AvlTree<T>::PrintInOrder(AVLNode<T> *root) const
{
    if (root == NULL)
    {
        return;
    }
    PrintInOrder(root->GetLeft());
    std::cout << root->GetValue() << " ";
    PrintInOrder(root->GetRight());
}

#endif // AVL_TREE_H