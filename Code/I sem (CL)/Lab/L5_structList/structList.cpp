#include "structList.h"
#include <iostream>
using namespace std;


// Дальше идёт Stack

//

template<typename type>
struct Stack
{
    type * lastElement = NULL;
};

template<typename type>
Stack<type> *init(type a)
{
    Stack<type> * pointer = (Stack<type> *)malloc(sizeof(Stack<type>));

}