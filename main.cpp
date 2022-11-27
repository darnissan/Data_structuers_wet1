
#include "orderedTriple.h"
#include "worldcup23a1.h"
#include <string>
#include <iostream>
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


void insertToTreeWithClosest(AvlTree<OrderedTriple> &tree, OrderedTriple &triple)
{
    if (tree.GetRoot() == NULL)
    {  
        tree.Insert(tree.GetRoot(), triple);
        return;
    }
    //NEEDS TO DO
    return ;
    
}
void ClosestDifffromRight(AVLNode<OrderedTriple> *node, OrderedTriple &searcher, OrderedTriple &minDiffcurrent)
{

    if (node == NULL)
    {
        return;
    }

    if (node->GetValue() > searcher && node->GetValue() < minDiffcurrent)
    {
        minDiffcurrent = node->GetValue();
    }

    if (node->GetValue().getThird() == searcher.getThird())
    {
        return ClosestDifffromRight(node->GetRight(), searcher, minDiffcurrent);
    }
    if (searcher < node->GetValue())
    {
        ClosestDifffromRight(node->GetLeft(), searcher, minDiffcurrent);
    }
    else
    {
        ClosestDifffromRight(node->GetRight(), searcher, minDiffcurrent);
    }
}
OrderedTriple ClosestDiffFromRightWrapper(AVLNode<OrderedTriple> *root, OrderedTriple &searcher)
{
    if (root == NULL)
    {
        return OrderedTriple(0,0,0);
    }

    OrderedTriple minDiffcurrent = OrderedTriple(INT_MAX, 0, -1);
    ClosestDifffromRight(root, searcher, minDiffcurrent);
    return minDiffcurrent;
}
    void ClosestDiffFromLeft(AVLNode<OrderedTriple> * node, OrderedTriple & searcher, OrderedTriple & minDiffcurrent)
    {

        if (node == NULL)
        {
            return;
        }

        if (node->GetValue() < searcher && node->GetValue() > minDiffcurrent)
        {
            minDiffcurrent = node->GetValue();
        }

        if (node->GetValue().getThird() == searcher.getThird())
        {
            return ClosestDiffFromLeft(node->GetLeft(), searcher, minDiffcurrent);
        }
        if (searcher < node->GetValue())
        {
            ClosestDiffFromLeft(node->GetLeft(), searcher, minDiffcurrent);
        }
        else
        {
            ClosestDiffFromLeft(node->GetRight(), searcher, minDiffcurrent);
        }
    }
    OrderedTriple ClosestDiffFromLeftWrapper(AVLNode<OrderedTriple> * root, OrderedTriple & searcher)
    {
        if (root == NULL)
        {
            return OrderedTriple(0, 0, 0);
        }

        OrderedTriple minDiffcurrent = OrderedTriple(-1, 0, -1);
        ClosestDiffFromLeft(root, searcher, minDiffcurrent);
        return minDiffcurrent;
    }

int closestsDealBreaker(OrderedTriple &triple,OrderedTriple &left,OrderedTriple &right)
{
    if (left==OrderedTriple(0,0,0))
    {
        return right.getThird();
    }
    else if (right==OrderedTriple(0,0,0))
    {
        return left.getThird();
    }
    else
    {
        
        if (abs(left.getFirst()-triple.getFirst())<abs(right.getFirst()-triple.getFirst()))
        {
            return left.getThird();
        }
        else if (abs(left.getFirst() - triple.getFirst()) > abs(right.getFirst() - triple.getFirst()))
        {
            return right.getThird();
        }
        else
        {
            if (abs(left.getSecond() - triple.getSecond()) < abs(right.getSecond() - triple.getSecond()))
            {
                return left.getThird();
            }
            else if (abs(left.getSecond() - triple.getSecond()) > abs(right.getSecond() - triple.getSecond()))
            {
                return right.getThird();
            }
            else
            {
                if (abs(left.getThird() - triple.getThird()) < abs(right.getThird() - triple.getThird()))
                {
                    return left.getThird();
                }
                else if (abs(left.getThird() - triple.getThird()) > abs(right.getThird() - triple.getThird()))
                {
                    return right.getThird();
                }
                else
                {
                    return max(left.getThird(), right.getThird());
                }
            }
        }
    }


}

int ClosestDealBreakerWrapper(AVLNode<OrderedTriple> *root, OrderedTriple &triple)
{
    OrderedTriple left = ClosestDiffFromLeftWrapper(root, triple);
    OrderedTriple right = ClosestDiffFromRightWrapper(root, triple);
    return closestsDealBreaker(triple, left, right);
}



    int main()
{

    AvlTree<OrderedTriple> tree;
    OrderedTriple a(1, 20, 21);
    OrderedTriple b(1, 20, 25);
    OrderedTriple c(1, 5, 3);
    OrderedTriple d(1, 1, 4);
    OrderedTriple e(2, 5, 5);
    OrderedTriple f(2, 4, 6);
    tree.root=tree.Insert(tree.GetRoot(),a);
    tree.root=tree.Insert(tree.GetRoot(),b);
    tree.root=tree.Insert(tree.GetRoot(),c);
    tree.root=tree.Insert(tree.GetRoot(),d);
    tree.root=tree.Insert(tree.GetRoot(),e);
    tree.root=tree.Insert(tree.GetRoot(),f);
    cout << f<< endl;
    cout << ClosestDiffFromLeftWrapper(tree.GetRoot(), f) << endl;
    cout << ClosestDiffFromRightWrapper(tree.GetRoot(), f) << endl;
    cout << ClosestDealBreakerWrapper(tree.GetRoot(), f) << endl;
    worldCup->add_team(1, 1);
    delete worldCup;  //  printBTs(tree.GetRoot());
    tree.PrintInOrder(tree.GetRoot());
    return 0;
}