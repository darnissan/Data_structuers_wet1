
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

int main()
{

    world_cup_t *worldCup = new world_cup_t();
    worldCup->add_team(1, 1);

    return 0;
}