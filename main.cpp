#include <string>

#include <sstream>
#include <vector>
#include <cassert>
#include <stdlib.h>


#include "orderedTriple.h"
#include "worldcup23a1.h"
#include <string>
#include <iostream>
#include <climits>
using namespace std;
void foo(StatusType t)
{
    
}
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
    // NEEDS TO DO
    return;
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
        return OrderedTriple(0, 0, 0);
    }

    OrderedTriple minDiffcurrent = OrderedTriple(INT_MAX, 0, -1);
    ClosestDifffromRight(root, searcher, minDiffcurrent);
    return minDiffcurrent;
}
void ClosestDiffFromLeft(AVLNode<OrderedTriple> *node, OrderedTriple &searcher, OrderedTriple &minDiffcurrent)
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
OrderedTriple ClosestDiffFromLeftWrapper(AVLNode<OrderedTriple> *root, OrderedTriple &searcher)
{
    if (root == NULL)
    {
        return OrderedTriple(0, 0, 0);
    }

    OrderedTriple minDiffcurrent = OrderedTriple(-1, 0, -1);
    ClosestDiffFromLeft(root, searcher, minDiffcurrent);
    return minDiffcurrent;
}

int closestsDealBreaker(OrderedTriple &triple, OrderedTriple &left, OrderedTriple &right)
{
    if (left == OrderedTriple(0, 0, 0))
    {
        return right.getThird();
    }
    else if (right == OrderedTriple(0, 0, 0))
    {
        return left.getThird();
    }
    else
    {

        if (abs(left.getFirst() - triple.getFirst()) < abs(right.getFirst() - triple.getFirst()))
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
    /*
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
        */
    // tree.PrintInOrder(tree.GetRoot());
    world_cup_t *obj = new world_cup_t();

    StatusType res = obj->add_team(1, 2);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_team(2, 2);
    //REQUIRE(res == StatusType::SUCCESS);

    // first team players
    res = obj->add_player(1001, 1, 1, 1, 1, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1002, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1003, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1004, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1005, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1006, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1007, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1008, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1009, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1010, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(1011, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);

    // second team players
    res = obj->add_player(2001, 2, 1, 1, 1, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2002, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2003, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2004, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2005, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2006, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2007, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2008, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2009, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2010, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->add_player(2011, 2, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);

    res = obj->play_match(1, 2);
    //REQUIRE(res == StatusType::SUCCESS);

    res = obj->remove_player(1001);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->play_match(1, 2);
    //REQUIRE(res == StatusType::FAILURE);
    res = obj->add_player(1001, 1, 1, 1, 1, false);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->play_match(1, 2);
    //REQUIRE(res == StatusType::FAILURE);
    res = obj->add_player(1020, 1, 1, 1, 1, true);
    //REQUIRE(res == StatusType::SUCCESS);
    res = obj->play_match(1, 2);
    //REQUIRE(res == StatusType::SUCCESS);

    delete obj;
    foo(res);
    delete obj;
    /*
    world_cup->add_player(25, 1, 1, 1, 20, true);
    world_cup->add_player(3, 1, 1, 1, 5, true);
    world_cup->add_player(4, 1, 1, 1, 1, true);
    world_cup->add_player(5, 2, 1, 2, 5, true);
    world_cup->add_player(6, 2, 1, 2, 4, true);
    world_cup->add_player(7, 1, 1, 3, 5, true);
    world_cup->add_player(8, 1, 1, 3, 4, true);
    world_cup->add_player(9, 1, 1, 4, 5, true);
    world_cup->add_player(10, 1, 1, 4, 4, true);
    world_cup->add_player(11, 1, 1, 3, 5, true);
    world_cup->add_player(12, 1, 1, 3, 4, true);
    world_cup->add_player(13, 1, 1, 4, 5, true);
    world_cup->add_player(14, 1, 1, 4, 4, true);
    world_cup->add_player(15, 1, 1, 3, 5, true);
    world_cup->add_player(16, 1, 1, 3, 4, true);
    world_cup->add_player(17, 1, 1, 4, 5, true);
    world_cup->add_player(18, 2, 1, 4, 4, true);
    world_cup->add_player(19, 2, 1, 3, 5, true);
    world_cup->add_player(20, 2, 1, 3, 4, true);
    world_cup->add_player(21, 2, 1, 4, 5, true);
    world_cup->add_player(22, 2, 1, 4, 4, true);
    world_cup->add_player(23, 2, 1, 3, 5, true);
    world_cup->add_player(24, 2, 1, 3, 4, true);
    world_cup->add_player(25, 2, 1, 4, 5, true);
    world_cup->add_player(26, 2, 1, 4, 4, true);
    world_cup->add_player(27, 2, 1, 3, 5, true);
    world_cup->add_player(28, 2, 1, 3, 4, true);
    world_cup->add_player(29, 2, 1, 4, 5, true);
    world_cup->add_player(30, 2, 1, 4, 4, true);

    world_cup->add_player(24, 2, 1, 2, 3, true);
    world_cup->add_player(7, 2, 1, 2, 2, true);
    world_cup->add_player(8, 3, 1, 2, 1, true);
    world_cup->add_player(9, 3, 1, 13, 5, true);
    world_cup->add_player(10, 3, 1, 15, 5, true);
    world_cup->add_player(11, 3, 1, 17, 5, true);
    world_cup->add_player(12, 3, 1, 14, 5, true);
    world_cup->add_player(13, 3, 1, 300, 5, true);
    // world_cup->printTeam(1);
    // world_cup->printTeam(2);
    world_cup->printInOrderAllPlayerStats();
    
    std::cout << "the closest of 21 is: " << world_cup->GetWinningClosestBySearcherID(1,21) << std::endl;
    std::cout << "the closest of 25 is: " << world_cup->GetWinningClosestBySearcherID(1,25) << std::endl;
    std::cout << "the closest of 3 is: " << world_cup->GetWinningClosestBySearcherID(1, 3) << std::endl;
    std::cout << "the closest of 4 is: " << world_cup->GetWinningClosestBySearcherID(1,4) << std::endl;
    std::cout << "the closest of 5 is: " << world_cup->GetWinningClosestBySearcherID(2, 5) << std::endl;
    std::cout << "the closest of 6 is: " << world_cup->GetWinningClosestBySearcherID(2,6) << std::endl;
    std::cout << "the closest of 7 is: " << world_cup->GetWinningClosestBySearcherID(1,7) << std::endl;
    std::cout << "the closest of 24 is: " << world_cup->GetWinningClosestBySearcherID(2, 24) << std::endl;
    std::cout << "the closest of 8 is: " << world_cup->GetWinningClosestBySearcherID(1, 8) << std::endl;
    std::cout << "the closest of 9 is: " << world_cup->GetWinningClosestBySearcherID(1, 9) << std::endl;
    std::cout << "the closest of 10 is: " << world_cup->GetWinningClosestBySearcherID(1, 10) << std::endl;
    std::cout << "the closest of 11 is: " << world_cup->GetWinningClosestBySearcherID(1,11) << std::endl;
    std::cout << "the closest of 12 is: " << world_cup->GetWinningClosestBySearcherID(1, 12) << std::endl;
    std::cout << "the closest of 13 is: " << world_cup->GetWinningClosestBySearcherID(1,13) << std::endl;
    
    std::cout<<"--------------------------------------"<<std::endl;

    world_cup->update_player_stats(21, 1,1,1);
    
    world_cup->printInOrderAllPlayerStats();
    std::cout << "the closest of 21 is: " << world_cup->GetWinningClosestBySearcherID(1, 21) << std::endl;
    std::cout << "the closest of 25 is: " << world_cup->GetWinningClosestBySearcherID(1, 25) << std::endl;
    std::cout << "the closest of 3 is: " << world_cup->GetWinningClosestBySearcherID(1, 3) << std::endl;
    std::cout << "the closest of 4 is: " << world_cup->GetWinningClosestBySearcherID(1, 4) << std::endl;
    std::cout << "the closest of 5 is: " << world_cup->GetWinningClosestBySearcherID(2, 5) << std::endl;
    std::cout << "the closest of 6 is: " << world_cup->GetWinningClosestBySearcherID(2, 6) << std::endl;
    std::cout << "the closest of 7 is: " << world_cup->GetWinningClosestBySearcherID(1, 7) << std::endl;
    std::cout << "the closest of 24 is: " << world_cup->GetWinningClosestBySearcherID(2, 24) << std::endl;
    std::cout << "the closest of 8 is: " << world_cup->GetWinningClosestBySearcherID(1, 8) << std::endl;
    std::cout << "the closest of 9 is: " << world_cup->GetWinningClosestBySearcherID(1, 9) << std::endl;
    std::cout << "the closest of 10 is: " << world_cup->GetWinningClosestBySearcherID(1, 10) << std::endl;
    std::cout << "the closest of 11 is: " << world_cup->GetWinningClosestBySearcherID(1, 11) << std::endl;
    std::cout << "the closest of 12 is: " << world_cup->GetWinningClosestBySearcherID(1, 12) << std::endl;
    std::cout << "the closest of 13 is: " << world_cup->GetWinningClosestBySearcherID(1, 13) << std::endl;

    std::cout << "--------------------------------------" << std::endl;

    world_cup->update_player_stats(25, 1,200,1);
    
    world_cup->printInOrderAllPlayerStats();
    std::cout << "the closest of 21 is: " << world_cup->GetWinningClosestBySearcherID(1, 21) << std::endl;
    std::cout << "the closest of 25 is: " << world_cup->GetWinningClosestBySearcherID(1, 25) << std::endl;
    std::cout << "the closest of 3 is: " << world_cup->GetWinningClosestBySearcherID(1, 3) << std::endl;
    std::cout << "the closest of 4 is: " << world_cup->GetWinningClosestBySearcherID(1, 4) << std::endl;
    std::cout << "the closest of 5 is: " << world_cup->GetWinningClosestBySearcherID(2, 5) << std::endl;
    std::cout << "the closest of 6 is: " << world_cup->GetWinningClosestBySearcherID(2, 6) << std::endl;
    std::cout << "the closest of 7 is: " << world_cup->GetWinningClosestBySearcherID(1, 7) << std::endl;
    std::cout << "the closest of 24 is: " << world_cup->GetWinningClosestBySearcherID(2, 24) << std::endl;
    std::cout << "the closest of 8 is: " << world_cup->GetWinningClosestBySearcherID(1, 8) << std::endl;
    std::cout << "the closest of 9 is: " << world_cup->GetWinningClosestBySearcherID(1, 9) << std::endl;
    std::cout << "the closest of 10 is: " << world_cup->GetWinningClosestBySearcherID(1, 10) << std::endl;
    std::cout << "the closest of 11 is: " << world_cup->GetWinningClosestBySearcherID(1, 11) << std::endl;
    std::cout << "the closest of 12 is: " << world_cup->GetWinningClosestBySearcherID(1, 12) << std::endl;
    std::cout << "the closest of 13 is: " << world_cup->GetWinningClosestBySearcherID(1, 13) << std::endl;

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

   world_cup->unite_teams(1, 4,4);
    world_cup->printTeam(4);
    world_cup->remove_player(27);
    world_cup->remove_player(28);
    world_cup->remove_player(29);

        world_cup->knockout_winner(2, 10);
    world_cup->printTeam(2);
    */

  //  printBTs(tree.GetRoot());

    return 0;
}