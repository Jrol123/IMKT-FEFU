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
    NodeStack<type> * pointerOnElementPrev = pointerOnElement;

    while(pointerOnElement->nextElement != NULL)
    {
        pointerOnElement = pointerOnElement->nextElement;
        free(pointerOnElementPrev);
        pointerOnElementPrev = pointerOnElement;
    }
    free(pointerOnElement);
    free(root);

    return true;

    //Need to test
}

template<typename type>
bool push(Stack<type> *root, type val)
{
    if(root == NULL)
    {
        return false;
    }

    root->lastElement->nextElement = (NodeStack<type> *)malloc(sizeof(NodeStack<type>));
    root->lastElement = root->lastElement->nextElement;
    *root->lastElement = val;

    if(root->firstElement == NULL)
    {
        root->firstElement = root->lastElement;
    }

    return true;
}

template<typename type>
bool pop(Stack<type> *root, type a)
{
    if(root == NULL)
    {
        return false;
    }

    NodeStack<type> * pointerOnElement = root->firstElement;

    while(pointerOnElement->nextElement->nextElement != NULL)
    {
        pointerOnElement = pointerOnElement->nextElement;
    }
    free(pointerOnElement->nextElement);
    root->lastElement = pointerOnElement;

    return true;
}

template<typename type>
type top(Stack<type> *root)
{
    return *root->lastElement;
}

template<typename type>
bool isEmpty(Stack<type> *root)
{
    if (root->lastElement == NULL)
    {
        return true;
    }
    return false;
}

// Дальше идёт Queue

//