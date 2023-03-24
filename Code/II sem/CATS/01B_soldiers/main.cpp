//#include <iostream>
#include <fstream>
using namespace std;

//typedef struct soldier
//{
//    float height;
//    string name;
//} soldiers_t;

void merge(float mass[], int start, int end, int mid, int length, int& countMoves)
{
    float mergedArr[length];
    int leftIndex, rightIndex, counter;
    leftIndex = start;
    counter = start;
    rightIndex = mid + 1;

    int countThrowers = 0;

    while (leftIndex <= mid && rightIndex <= end)
    {
        if (mass[leftIndex] >= mass[rightIndex])
        {
            mergedArr[counter] = mass[leftIndex];
            counter++;
            leftIndex++;
            countMoves += countThrowers;
        } // Если перескока не происходит
        else
        {
            mergedArr[counter] = mass[rightIndex];

            counter++;
            rightIndex++;
            countThrowers ++;
        } // Перескок
    } // Пока не вышли за пределы области

    while (leftIndex <= mid)
    {
        mergedArr[counter] = mass[leftIndex];
        counter++;
        leftIndex++;
        countMoves += countThrowers;
    } // Слив левой части. Необходимо "перебрасывать"

    while (rightIndex <= end)
    {
        mergedArr[counter] = mass[rightIndex];
        counter++;
        rightIndex++;
    } // Слив правой части. Происходит "безболезненно"

    for (leftIndex = start; leftIndex < counter; leftIndex++)
    {
        mass[leftIndex] = mergedArr[leftIndex];
    } // Перевод в нормальный массив
}

void mergeSort(float mass[], int start, int end, int length, int& countMoves)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(mass, start, mid, length, countMoves);
        mergeSort(mass, mid + 1, end, length, countMoves);
        merge(mass, start, end, mid, length, countMoves);
    }
}

int main()
{
    ifstream inf("input.txt");

    int countOfSoldiers;
    inf >> countOfSoldiers;
    float massSoldiers [countOfSoldiers];
//    soldiers_t finalSoldiers [countOfSoldiers];
    for(int i = 0; i < countOfSoldiers; i++)
    {
        inf >> massSoldiers[i];
        string name;
        inf >> name;
    }
    inf.close();

    int count = 0;
    mergeSort(massSoldiers, 0, countOfSoldiers - 1, countOfSoldiers, count);

    ofstream outf("output.txt");
    outf << count;
    outf.close();
}
