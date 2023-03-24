#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct soldier
{
    float height;
    string name;
} soldiers_t;

void merge(soldiers_t arr[], int start, int end, int mid, int length, int& countMoves)
{
    soldiers_t mergedArr[length];
//    int mergedIndexes[length];
    int leftIndex, rightIndex, counter;
    leftIndex = start;
    counter = start;
    rightIndex = mid + 1;

    int countThrowers = 0;

    while (leftIndex <= mid && rightIndex <= end)
    {
        if (arr[leftIndex].height >= arr[rightIndex].height)
        {
            // cout << arr[leftIndex] << " " << arr[rightIndex] << endl;
            mergedArr[counter] = arr[leftIndex];
            counter++;
            leftIndex++;
            countMoves += countThrowers;
        } // Если перескока не происходит
        else
        {
            // cout << arr[leftIndex] << " | " << arr[rightIndex] << endl;
            mergedArr[counter] = arr[rightIndex];

            counter++;
            rightIndex++;
            countThrowers ++;
        } // Перескок
    } // Пока не вышли за пределы области

    while (leftIndex <= mid)
    {
        mergedArr[counter] = arr[leftIndex];
        counter++;
        leftIndex++;
        countMoves += countThrowers;
    } // Слив левой части. Необходимо "перебрасывать"

    while (rightIndex <= end)
    {
        mergedArr[counter] = arr[rightIndex];
        counter++;
        rightIndex++;
    } // Слив правой части. Происходит "безболезненно"

    for (leftIndex = start; leftIndex < counter; leftIndex++)
    {
        arr[leftIndex] = mergedArr[leftIndex];
//        indexes[leftIndex] = mergedIndexes[leftIndex];
    } // Перевод в нормальный массив
}

void mergeSort(soldiers_t arr[], int start, int end, int length, int& countMoves)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid, length, countMoves);
        mergeSort(arr, mid + 1, end, length, countMoves);
        merge(arr, start, end, mid, length, countMoves);
    }
}

// index-needIndex это кол-во операций, необходимое для перемещения элемента
// с index до needIndex
int main()
{
    ifstream inf("input.txt");

    int countOfSoldiers;
    inf >> countOfSoldiers;
    soldiers_t massSoldiers [countOfSoldiers];
//    soldiers_t finalSoldiers [countOfSoldiers];
    for(int i = 0; i < countOfSoldiers; i++)
    {
        inf >> massSoldiers[i].height;
        inf >> massSoldiers[i].name;
    }
    inf.close();

    int count = 0;
    mergeSort(massSoldiers, 0, countOfSoldiers - 1, countOfSoldiers, count);

    ofstream outf("output.txt");
    outf << count;
    outf.close();
}
