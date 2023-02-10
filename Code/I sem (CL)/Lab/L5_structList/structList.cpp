#include "structList.h"
#include <iostream>
using namespace std;


// Дальше идёт Stack

//

template<typename type>
struct NodeStack
{
    type a;
    NodeStack<type> * nextElement = NULL;
};

// Поскольку это Stack, то необходимо оперировать последним элементом.
// Поскольку это list, то необходимо иметь ссылку на первый элемент.

//Из этого следует, что нужно работать с системой Node

template<typename type>
struct Stack
{
    NodeStack<type>  * lastElement = NULL;
    NodeStack<type> * firstElement = NULL;
};

template<typename type>
Stack<type> *init(type a)
{
    Stack<type> * pointer = (Stack<type> *)malloc(sizeof(Stack<type>));

}