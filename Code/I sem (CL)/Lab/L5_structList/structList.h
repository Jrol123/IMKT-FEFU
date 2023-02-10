#ifndef L5_STRUCTLIST_STRUCTLIST_H
#define L5_STRUCTLIST_STRUCTLIST_H

template<typename type>
struct NodeStack;

template<typename type>
struct Stack;

template<typename type>
Stack<type> *init(type val);

template<typename type>
bool deInit(Stack<type> *root);

#endif //L5_STRUCTLIST_STRUCTLIST_H
