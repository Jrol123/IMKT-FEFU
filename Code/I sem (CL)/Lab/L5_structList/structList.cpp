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