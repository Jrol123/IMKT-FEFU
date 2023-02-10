#include "structArray.h"
#include <iostream>
using namespace std;

// Дальше идёт Stack

template<typename type>
struct Stack
{
    int maxSize;
    type top;
    type *firstElement = NULL;
};

// Дальше идёт QUEUE

// First in — first out
// Поскольку реализация идёт через Array (Динамический массив), то всё находится рядом.
// При инициализации Queue идёт выделение кучи ячеек под NodeQueue

// Я решил создать отдельно struct Queue и отдельно struct NodeQueue, для хранения разной инф-и.
// Можно было бы в каждом NodeQueue хранить информацию, но что толку?
// Мне кажется, это только будет мешать.
// Хотя, так не надо будет создавать доп. структуру (Queue)...

// Как можно один раз инициализировать type и всё?
// И как можно хранить type, как, например, в vector?!
// https://habr.com/ru/post/207294/
// Сложно...

template<typename type>
struct Queue
{
    int maxSize;
    int curSize;
    type *firstElement = NULL;
    // Разобраться с удалением первого элемента.
    // Необходимо смещать и все остальные?
    // Через цикл
};


template<typename type>
Queue<type> *init(int maxSize, type a)
{
//    auto typeDefin = type;
    auto *pointer = (Queue<type> *)malloc(sizeof(Queue<type>)); // Указатель на Queue
    if (pointer == NULL)
    {
        return NULL;
    }
    pointer->maxSize = maxSize;
    pointer->curSize = 1;
    pointer->firstElement = (type *)malloc(maxSize * sizeof(type));
    *(pointer->firstElement) = a;
    return pointer;
}

template<typename type>
bool deInit(Queue<type> *root)
{
    if (root == NULL)
    {
        return false;
    }
    for(int i = root->curSize - 1; i >= 0; i--)
    {
        free(root->firstElement + i);
    }
    free(root);
    return true;
}

template<typename type>
bool addTail(Queue<type> *root, type value)
{
    if (root->curSize == root->maxSize)
    {
        return false;
    }
    *(root->firstElement + root->curSize - 1) = value;
    return true;
}

template<typename type>
bool pop(Queue<type> *root)
{
    if (root == NULL)
    {
        return false;
    }
    for(int i = 0; i <= root->curSize - 2; i++)
    {
        *(root->firstElement + i) = *(root->firstElement + i + 1);
    }
    root->curSize -= 1;
    return true;
}
// Через связанные списки было бы проще

template<typename type>
type front(Queue<type> *root)
{
    if (root->curSize != 0)
    {
        return *(root->firstElement);
    }
    return -int('-inf');
}

template<typename type>
bool isEmpty(Queue<type> *root)
{
    if (root->curSize == 0)
    {
        return true;
    }
    return false;
}

//template<typename type>
//type calc(Queue<type> *root)
//{
//    return *(root->firstElement) + 1;
//}