#include "structList.h"
#include <iostream>
using namespace std;


// Дальше идёт Stack

//

template<typename type>
struct NodeStack
{
    type val;
    NodeStack<type> * nextElement = NULL;
};

// Поскольку это Stack, то необходимо оперировать последним элементом.
// Поскольку это list, то необходимо иметь ссылку на первый элемент.

//Из этого следует, что нужно работать с системой Node

template<typename type>
struct Stack
{
    NodeStack<type> * lastElement = NULL;
    NodeStack<type> * firstElement = NULL;
};

template<typename type>
Stack<type> *init(type val)
{
    Stack<type> * pointer = (Stack<type> *)malloc(sizeof(Stack<type>));

    if (pointer == NULL)
    {
        return NULL;
    }

    pointer->firstElement = (NodeStack<type> *)malloc(sizeof(NodeStack<type>));
    *pointer->firstElement->val = val;
    pointer->firstElement = pointer->lastElement;

    return pointer;
}
template<typename type>
bool deInit(Stack<type> *root)
{
    if(root == NULL)
    {
        return false;
    }
    NodeStack<type> * pointerOnElement = root->firstElement;
    NodeStack<type> * pointerOnElementPr = pointerOnElement;

    while(pointerOnElement->nextElement != NULL)
    {
        pointerOnElement = pointerOnElement->nextElement;
        free(pointerOnElementPr);
        pointerOnElementPr = pointerOnElement;
    }
    free(pointerOnElement);
    free(root);

    //Need to test
}