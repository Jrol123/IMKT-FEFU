#ifndef L5_STRUCTLIST_STRUCTLIST_H
#define L5_STRUCTLIST_STRUCTLIST_H


// Дальше идёт Stack

template<typename type>
struct NodeStack;

template<typename type>
struct Stack;

template<typename type>
Stack<type> *init(type val);

template<typename type>
bool deInit(Stack<type> *root);

template<typename type>
bool push(Stack<type> *root, type val);

template<typename type>
bool pop(Stack<type> *root);

template<typename type>
bool top(Stack<type> *root);

template<typename type>
bool isEmpty(Stack<type> *root);

// Дальше идёт Queue

//

#endif //L5_STRUCTLIST_STRUCTLIST_H
