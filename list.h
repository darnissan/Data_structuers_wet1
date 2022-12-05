#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include "AvlTree.h"
// Define a template class for a node in the linked list
class IDandTotalPoints
{
    int id;
    int totalPoints;

public:
    int getId() const
    {
        return id;
    }
    int getTotalPoints() const
    {
        return totalPoints;
    }
    IDandTotalPoints(int id, int totalPoints) : id(id), totalPoints(totalPoints)
    {
    }
    void setTotalPoints(int totalPoints)
    {
        this->totalPoints = totalPoints;
    }
    void setId(int id)
    {
        this->id = id;
    }
    friend std::ostream &operator<<(std::ostream &os, const IDandTotalPoints &idAndTotalPoints)
    {
        os << "id: " << idAndTotalPoints.id << " totalPoints: " << idAndTotalPoints.totalPoints;
        return os;
    }
};

template <class T>
class ListNode
{
public:
    // Constructor to initialize the node with a given value
    ListNode(const T &value) : value(value), next(nullptr) {}

    // Getter and setter methods for the value and next pointer of the node
    const T &GetValue() const { return value; }
    void SetValue(const T &value) { this->value = value; }

    ListNode *GetNext() const { return next; }
    void SetNext(ListNode *next) { this->next = next; }

private:
    // The value and next pointer of the node
    T value;
    ListNode *next;
};

// Define a template class for the linked list
template <class T>
class LinkedList
{
public:
    // Default constructor to initialize the head and tail pointers of the list
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor to free the memory used by the nodes in the list
    ~LinkedList()
    {
        // Iterate through the list and delete each node
        ListNode<T> *node = head;
        while (node != nullptr)
        {
            ListNode<T> *next = node->GetNext();
            delete node;
            node = next;
        }
    }

    // Getter and setter methods for the head and tail pointers of the list
    ListNode<T> *GetHead() const
    {
        return head;
    }
    void SetHead(ListNode<T> *head) { this->head = head; }

    ListNode<T> *GetTail() const { return tail; }
    void SetTail(ListNode<T> *tail) { this->tail = tail; }

    // Method to insert a new node with a given value at the end of the list
    void Insert(const T &value)
    {
        // Create a new node with the given value
        ListNode<T> *node = new ListNode<T>(value);

        // If the list is empty, set the new node as the head and tail of the list
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        // Otherwise, add the new node to the end of the list and update the tail pointer
        else
        {
            tail->SetNext(node);
            tail = node;
        }
    }
    // Method to remove a node with a given value from the list
    void Remove(const T &value)
    {
        // Keep track of the previous and current nodes as we iterate through the list
        ListNode<T> *prev = nullptr;
        ListNode<T> *node = head;

        // Iterate through the list until we find a node with the given value
        while (node != nullptr && node->GetValue() != value)
        {
            prev = node;
            node = node->GetNext();
        }

        // If we found a node with the given value, remove it from the list
        if (node != nullptr)
        {
            // If the node is the head of the list, update the head pointer
            if (node == head)
                head = node->GetNext();
            // If the node is the tail of the list, update the tail pointer
            else if (node == tail)
                tail = prev;

            // If the previous node is not null, update its next pointer
            // to point to the node after the one that we're removing
            if (prev != nullptr)
                prev->SetNext(node->GetNext());

            // Delete the node that we're removing
            delete node;
        }
    }



    bool IsEmpty() const
    {
        return head == nullptr;
    }

    // Method to append the values from another linked list to the end of this list
    void Append(const LinkedList<T> &other)
    {
        // Check if the other list is empty. If it is, there is nothing to append,
        // so we can return immediately.
        if (other.IsEmpty())
            return;

        // If this list is empty, we can simply set the head and tail pointers
        // to point to the head and tail of the other list.
        if (IsEmpty())
        {
            head = other.head;
            tail = other.tail;
        }
        // If this list is not empty, we need to iterate through the list
        // to find the last node, and then update its next pointer to point
        // to the head of the other list.
        else
        {
            ListNode<T> *node = head;
            while (node->GetNext() != nullptr)
                node = node->GetNext();
            node->SetNext(other.head);
            tail = other.tail;
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const LinkedList<T> &list)
    {
        ListNode<T> *node = list.head;
        while (node != nullptr)
        {
            os << node->GetValue() << " ";
            node = node->GetNext();
        }
        return os;
    }

    void getValuesInRange(AVLNode<Team> *node, int min, int max)
    {
        if (node == NULL)
        {
            return;
        }
        if (node->GetValue().getId() <= max && node->GetValue().getId() >= min)
        {
            this->getValuesInRange(node->GetLeft(), min, max);
            //if (node->GetValue().getNumOfPlayers() >= 11 && node->GetValue().getNumOfGoalKeepers() >= 1)
            //{
                this->Insert(IDandTotalPoints(node->GetValue().getId(), node->GetValue().getPoints()));
            //}
            
            this->getValuesInRange(node->GetRight(), min, max);
        }
        if (node->GetValue().getId() > max && node->GetLeft() != NULL)
        {
            this->getValuesInRange(node->GetLeft(), min, max);
        }
        else if (node->GetValue().getId() < min && node->GetRight() != NULL)
        {
            this->getValuesInRange(node->GetRight(), min, max);
        }
    }

private:
    // The head and tail pointers of the linked list
    ListNode<T> *head;
    ListNode<T> *tail;
};
#endif // LIST_H_