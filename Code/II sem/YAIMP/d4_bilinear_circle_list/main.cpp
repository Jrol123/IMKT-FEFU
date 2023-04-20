#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node * next = nullptr;
    Node * prev = nullptr;
};

struct List
{
    Node * first = nullptr;
    Node * last = nullptr;

    List(int val)
    {
        this-> first = new Node (val);
        this-> last = this->first;

        this->first->next = this->last;
        this->last->prev = this->first;
    }

    void push (int val)
    {
        if(first == last & first == nullptr)
        {
            this-> first = new Node (val);
            this-> last = this->first;

            this->first->next = this->last;
            this->last->prev = this->first;
            return;
        } //

        Node * node = new Node(val);
        node->next = this->first; node->prev = this->last;
        this->last->next = node;
        this->first->prev = node;
        this->last = node;
    }

    bool pop(Node * node)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (node == this-> first & node == this-> last)
        {
            free(node);
            this->first = nullptr; this->last = nullptr;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if(node == this->first)
            {
                this->first = node->next;
            }
            else if(node == this->last)
            {
                this->last = node->prev;
            }
            free(node);
        }
        return true;
    }
    void print()
    {
        Node * cur = this-> first;
        int index = 1;

        do
        {
            cout << index << ")  " <<  cur-> val << endl;
            cur = cur->next;
            index ++;

        }while(cur != this->first);

        cout << endl;
    }
};

int main()
{
    List* a = new List(0);
    a->pop(a->first);
    a->push(1);
    a->push(2);
    a->push(3);
    a->print();
//    Node* cur = a->last;
    a->pop(a->first);
    a->print();
}
