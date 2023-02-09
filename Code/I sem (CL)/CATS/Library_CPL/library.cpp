#include "library.h"

#include <iostream>
typedef int type_t;

typedef struct Node {
    type_t value;
    struct Node* next;
} tNode;

typedef struct Stack
{
    tNode* begin;
    type_t maxsize;
    type_t currentsize;
}Stack_t;

struct Stack * init(int a, int maxSize) // Возвращает структуру
{
    auto ptr = (int *)malloc(maxSize);
    ptr->begin = NULL;
    ptr->currentsize = 0;
    ptr->maxsize = maxSize;
    return ptr;
}