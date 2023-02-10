#include <iostream>
#include "structList.cpp"
//#include "structArray.cpp"
// Conflict in namings betwen Array and List

int main()
{
//    Queue<int> *pointer1 = init<int>(10, 79);
//    Queue<bool> *pointer2 = init<bool>(3, false);
//    Error (issue)

    Stack<int> *pt1 = init<int>(10);
    pop(pt1);
    isEmpty(pt1);
}
