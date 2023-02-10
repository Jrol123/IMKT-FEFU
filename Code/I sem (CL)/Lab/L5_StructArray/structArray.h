#ifndef L5_STRUCTARRAY_STRUCTARRAY_H
#define L5_STRUCTARRAY_STRUCTARRAY_H

template<typename type>
struct Stack;

// Queue

template<typename type>
struct Queue;

template<typename type>
Queue<type> *init(int maxSize, type a);

template<typename type>
bool deInit(Queue<type> *root);

template<typename type>
bool addTail(Queue<type> *root, type value);

template<typename type>
bool pop(Queue<type> *root);

template<typename type>
type front(Queue<type> *root);

template<typename type>
bool isEmpty(Queue<type> *root);

#endif //L5_STRUCTARRAY_STRUCTARRAY_H
