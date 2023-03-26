//#include <iostream>
#include <fstream>
//#include <cmath>
using namespace std;

void siftUpMax(int mass [], int massIndexes[], int index, int countEl)
{
    while(mass[index] > mass[(index - 1) / 2])
    {
        swap(mass[index], mass[(index - 1) / 2]);
        swap(massIndexes[massIndexes[index]],massIndexes[massIndexes[(index - 1) / 2]]);
        index = (index - 1) / 2;
    }
}

void siftDownMax(int mass [], int massIndexes[], int index, int countEl)
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
        swap(massIndexes[massIndexes[index]],massIndexes[massIndexes[subIndex]]);
        index = subIndex; // Индекс меняемого элемента
    }
}

void buildHeapMax(int mass [], int massIndexes [], int countEl)
{
    for(int i = countEl / 2; i >= 0; --i)
    {
        siftDownMax(mass, massIndexes, i, countEl);
    }
}

int main()
{
    ifstream inf("input.txt");
    int countWorkers, countDiff;
    inf >> countWorkers >> countDiff;
    int massWorkers [countWorkers];

    int massIndexes [countWorkers][1];

    for(int i = 0; i < countWorkers; i++)
    {
        inf >> massWorkers[i];
        massIndexes[i][0] = i;
    }
    buildHeapMax(massWorkers, * massIndexes, countWorkers);

    ofstream outf("output.txt");

    for (int i = 0; i < countDiff; ++i)
    {
        int index, diff;
        inf >> index >> diff;
        index = massIndexes[index - 1][0]; // Проверить на 0 0 0 -10 -20 -30. Неправильно свапает индексы

        massWorkers[index] += diff;
        if (diff > 0)
        {
            siftUpMax(massWorkers, *massIndexes, index, countWorkers);
        }
        else
        {
            siftDownMax(massWorkers, *massIndexes, index, countWorkers);
        }
        outf << massWorkers[0] << endl;
    }

    inf.close();
    outf.close();
}
