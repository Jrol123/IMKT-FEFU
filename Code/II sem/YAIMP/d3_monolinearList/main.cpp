#include <iostream>
using namespace std;

//struct Data
//{
//    int val;
//
//    bool operator>(Data other)
//    {
//         return (this->val > other.val);
//    }
//};

struct Node
{
//    Data val;
    int val;
    Node * next = nullptr;
};

struct List
{
    Node * first = nullptr;

    List(int val)
    {
        this-> first = new Node (val);
    }

    void push_front(int val)
    {
        Node * tempFirstNode = first;
        this-> first = new Node (val);
        this->first-> next = tempFirstNode;
   } // Недоделано

    void push (int val)
    {
        Node * prevNode = first;
        if (first->val > val)
        {
            push_front(val);
//            this-> first = new Node (val);
//            this->first-> next = prevNode;
//            return;
// 6
//2 1 0 10 10 -10
//
        } // Добавление элемента слева
        while (prevNode-> next != nullptr)
        {
            if (prevNode->next->val > val)
            {
                prevNode->next = new Node(val, prevNode->next);
                return;
            }
            prevNode = prevNode-> next;
        }
        prevNode-> next = new Node (val); // Добавление элемента справа
   } // Неубывающий список
};

int main()
{
    int countElements;
    cin >> countElements;

    int element;
    cin >> element;
    List testList(element);
    for(int i = 1; i < countElements; i++)
    {
        cin >> element;
        testList.push(element);
    }
    cout << endl;
    Node * cur = testList.first;
    for(int i = 0; i <  countElements; i++)
    {
        cout << cur->val << " ";
        cur = cur-> next;
    }

//    List testList(Data(1));
//    testList.push(0);
//    testList.push(2);
}
