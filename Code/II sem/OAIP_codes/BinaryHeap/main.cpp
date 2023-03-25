#include <iostream>
using namespace std;

void siftDownMin(int mass [], int index, int countEl)
{
    while (2 * index + 1 < countEl)
    {
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;

        int subIndex = leftIndex;
        if(rightIndex < countEl and mass[rightIndex] < mass[leftIndex])
        {
            subIndex = rightIndex;
        } // Выбор наименьшего ребёнка
        if(mass[index] <= mass[subIndex])
        {
            break;
        } // Если всё в порядке
        swap(mass[index], mass[subIndex]);
        index = subIndex; // Индекс меняемого элемента
    }
}

void siftDownMax(int mass [], int index, int countEl)
{
    while (2 * index + 1 < countEl)
    {
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;

        int subIndex = leftIndex;
        if(rightIndex < countEl and mass[rightIndex] > mass[leftIndex])
        {
            subIndex = rightIndex;
        } // Выбор наименьшего ребёнка
        if(mass[index] >= mass[subIndex])
        {
            break;
        } // Если всё в порядке
        swap(mass[index], mass[subIndex]);
        index = subIndex; // Индекс меняемого элемента
    }
}

void buildHeapMin(int mass [], int countEl)
{
    for(int i = countEl / 2; i >= 0; --i)
    {
        siftDownMin(mass, i, countEl);
    }
}

void buildHeapMax(int mass [], int countEl)
{
    for(int i = countEl / 2; i >= 0; --i)
    {
        siftDownMax(mass, i, countEl);
    }
}

int main()
{
    int mass1[] {1, 2, 5, 70, 66, 30, 4};
    int mass2[] {1, 2, 5, 70, 66, 30, 4};
    buildHeapMin(mass1, 7);
    buildHeapMax(mass2, 7);
    cout << mass1[0] << endl << mass2[0];
}
