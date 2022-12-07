#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>

template <class T>
class AVLNode
{
public:
    AVLNode(const T &value) : data(value), left(NULL), right(NULL) {}
    ~AVLNode() {}
    void SetValue(const T &value) { data = value; }
    const T &GetValue() const { return data; }
    T &GetValue() { return data; }
    void SetLeft(AVLNode *node) { left = node; }
    AVLNode *GetLeft() const { return left; }
    void SetRight(AVLNode *node) { right = node; }
    AVLNode *GetRight() const { return right; }

    void Print() const { std::cout << data << std::endl; }
    AVLNode() = default;

private:
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
    bool isItInTree(AVLNode<T> *root, const T &value) const;
    AVLNode<T> *Insert(AVLNode<T> *root, const T &value);
    AVLNode<T> *Remove(AVLNode<T> *node, const T &value);
    void PrintInOrder(AVLNode<T> *root) const;
    void DeleteTree(AVLNode<T> *root);
    void Clear();
    AVLNode<T> *Clear(AVLNode<T> *root);

private:
    void DeleteAvlNode(AVLNode<T> *nodeToRemove); // function used by the destructor
};
template <class T>
void AvlTree<T>::DeleteTree(AVLNode<T> *node)
{
    if (node == NULL)
    {
        return;
    }
    node->SetLeft(this->Clear(node->GetLeft()));
    node->SetRight(this->Clear(node->GetRight()));
    delete node;
    node=NULL;
    return;
}
template <class T>
AvlTree<T>::~AvlTree()
{
    this->Clear();
}
template <class T>
void AvlTree<T>::Clear()
{
    
        this->root = this->Clear(this->root);
        this->root = NULL;
    
}

template <class T>
AVLNode<T> *AvlTree<T>::Clear(AVLNode<T> *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    node->SetLeft(this->Clear(node->GetLeft()));
    node->SetRight(this->Clear(node->GetRight()));
    delete node;
    node=NULL;
    return NULL;
}
template <class T>
void AvlTree<T>::DeleteAvlNode(AVLNode<T> *nodeToRemove)
{
    if (nodeToRemove)
    {
        if (nodeToRemove->GetLeft())
        {
            DeleteAvlNode(nodeToRemove->GetLeft());
        }
        if (nodeToRemove->GetRight())
        {
            DeleteAvlNode(nodeToRemove->GetRight());
        }

        delete nodeToRemove;
    }
}
template <class T>
AVLNode<T> *AvlTree<T>::find(AVLNode<T> *node, const T &value) const
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->GetValue() == value)
    {
        return node;
    }
    if (node->GetValue() > value)
    {
        return find(node->GetLeft(), value);
    }
    else
    {
        return find(node->GetRight(), value);
    }
}
template <class T>
int AvlTree<T>::height(AVLNode<T> *node) const
{
    int Ownheight = 0;
    if (node == NULL)
    {
        return 0;
    }
    int leftHeight = height(node->GetLeft());
    int rightHeight = height(node->GetRight());
    Ownheight = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    return Ownheight;
}
template <class T>
int AvlTree<T>::GetBF(AVLNode<T> *node) const
{
    int leftHeight = height(node->GetLeft());
    int rightHeight = height(node->GetRight());
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
    AVLNode<T> *temp = RotateRR(node->GetLeft());
    node->SetLeft(temp->GetRight());
    temp->SetRight(node);
    node = temp;
    return node;
}
template <class T>
AVLNode<T> *AvlTree<T>::RotateRL(AVLNode<T> *node)
{
    AVLNode<T> *temp = RotateLL(node->GetRight());
    node->SetRight(temp->GetLeft());
    temp->SetLeft(node);
    node = temp;
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
AVLNode<T> *AvlTree<T>::Remove(AVLNode<T> *node, const T &value)
{
    if (node == NULL) // meaning we've reached a Null
    {
        return NULL;
    }
    if (value < node->GetValue()) // Meaning value to remove is in the left Subtree
    {
        node->SetLeft(this->Remove(node->GetLeft(), value));
    }
    else if (value > node->GetValue())
    {
        node->SetRight(this->Remove(node->GetRight(), value));
    }
    else if (value == node->GetValue())
    {
        if (node->GetLeft() == NULL && node->GetRight() == NULL)
        {
            if (node == this->root)
            {
                this->root = NULL;
            }
            delete node;
            node=NULL;
            return NULL;
        }
        else if (node->GetLeft() == NULL)
        {
            AVLNode<T> *temp = node->GetRight();
            delete node;
            node = NULL;
            return temp;
        }
        else if (node->GetRight() == NULL)
        {
            AVLNode<T> *temp = node->GetLeft();
            delete node;
            node = NULL;
            return temp;
        }
        else
        {
            AVLNode<T> *temp = node->GetRight();
            while (temp->GetLeft() != NULL)
            {
                temp = temp->GetLeft();
            }
            node->SetValue(temp->GetValue());
            node->SetRight(Remove(node->GetRight(), temp->GetValue()));
        }
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
template <class T>
bool AvlTree<T>::isItInTree(AVLNode<T> *node, const T &value) const
{
    if (node == NULL)
    {
        return false;
    }
    if (node->GetValue() == value)
    {
        return true;
    }
    if (node->GetValue() > value)
    {
        return isItInTree(node->GetLeft(), value);
    }
    else
    {
        return isItInTree(node->GetRight(), value);
    }
    return false;
}
#endif // AVL_TREE_H