#ifndef ORDERD_TRIPLE_H_
#define ORDERD_TRIPLE_H_
#include <iostream>

class OrderedTriple
{
private:
    int first;
    int second;
    int third;

public:
    OrderedTriple(int first, int second, int third)
    {
        this->first = first;
        this->second = second;
        this->third = third;
    }
    int getFirst() const
    {
        return first;
    }
    int getSecond() const
    {
        return second;
    }
    int getThird() const
    {
        return third;
    }
    bool operator<(const OrderedTriple &other) const
    {
        if (first < other.first)
            return true;
        if (first > other.first)
            return false;
        if (first == other.first)
        {
            if (second < other.second)
                return false;
            if (second > other.second)
                return true;
            if (second == other.second)
            {
                if (third < other.third)
                    return true;
                if (third > other.third)
                    return false;
            }
        }
        return false;
    }
    bool operator>(const OrderedTriple &other) const
    {
        if (first > other.first)
            return true;
        if (first < other.first)
            return false;
        if (first == other.first)
        {
            if (second > other.second)
                return false;
            if (second < other.second)
                return true;
            if (second == other.second)
            {
                if (third > other.third)
                    return true;
                if (third < other.third)
                    return false;
            }
        }
        return false;
    }
    bool operator==(const OrderedTriple &other) const
    {
        if (first == other.first && second == other.second && third == other.third)
            return true;
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const OrderedTriple &triple)
    {
        os << "(" << triple.first << "," << triple.second << "," << triple.third << ")";
        return os;
    }
};
#endif // ORDERD_TRIPLE_H_