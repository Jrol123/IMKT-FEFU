#include <iostream>
#include <fstream>
using namespace std;

void merge(int arr[], int indexes[][2], int start, int end, int mid, int L)
{
    int mergedArr[L];
    int mergedIndexes[L];
    int i, j, k;
    i = start;
    k = start;
    j = mid + 1;

    while (i <= mid && j <= end)
    {
        if (arr[i] <= arr[j])
        {
            // cout << arr[i] << " " << arr[j] << endl;
            mergedArr[k] = arr[i];
            mergedIndexes[k] = indexes[i][0];
            k++;
            i++;
        }
        else
        {
            // cout << arr[i] << " | " << arr[j] << endl;
            mergedArr[k] = arr[j];
            mergedIndexes[k] = indexes[j][0];

            k++;
            j++;
        }
    }

    while (i <= mid)
    {
        mergedArr[k] = arr[i];
        mergedIndexes[k] = indexes[i][0];
        k++;
        i++;
    }

    while (j <= end)
    {
        mergedArr[k] = arr[j];
        mergedIndexes[k] = indexes[j][0];
        k++;
        j++;
    }

    for (i = start; i < k; i++)
    {
        arr[i] = mergedArr[i];
        indexes[i][0] = mergedIndexes[i];
    }
}

void mergeSort(int arr[], int indexes[][2], int start, int end, int L)
{
    int mid;
    if (start < end)
    {
        mid = (start + end) / 2;
        mergeSort(arr, indexes, start, mid, L);
        mergeSort(arr, indexes, mid + 1, end, L);
        merge(arr, indexes, start, end, mid, L);
    }
}

int binarySearch(int findNum, int bottomPos, int upperPos, int mass[])
{
    bool state = false;
    int nowPos = (upperPos + bottomPos)/2;
    int nowNum = mass[nowPos];
    if(upperPos < bottomPos || findNum == nowNum)
    {
        return nowPos;
    }
    else
    {
        if (findNum > nowNum)
        {
            bottomPos = nowPos + 1;
        }
        else
        {
            upperPos = nowPos - 1;
        }
        return binarySearch(findNum, bottomPos, upperPos, mass);
    }
}

int main()
{
    ifstream inf ("shelter.in");
    ofstream outf ("shelter.out");

    int countOfSel, countOfBombShelters;

    inf >> countOfSel;
    int distancesSel [countOfSel];

    for(int i = 0; i < countOfSel; i++)
    {
        int distanceSel;
        inf >> distanceSel;
        distancesSel[i] = distanceSel;
    }

    inf >> countOfBombShelters;
    int indexesB [countOfBombShelters][2];
    int distancesBombShelters [countOfBombShelters];

    for(int i = 0; i < countOfBombShelters; i++)
    {
        int distanceBombShelter;
        inf >> distanceBombShelter;
        distancesBombShelters[i] = distanceBombShelter;
        indexesB[i][0] = i + 1;
        indexesB[i][0] = i + 1;
    }

    inf.close();

    mergeSort(distancesBombShelters, indexesB, 0, countOfBombShelters - 1, countOfBombShelters);

    for(int i = 0; i < countOfSel; i++)
    {
        int num = distancesSel[i];
        int midIndex = binarySearch(num, 0, countOfBombShelters, distancesBombShelters);
        int diffNum = abs(distancesSel[i] - distancesBombShelters[midIndex]);
        int diff = 0;

        if (midIndex > 0 && abs(num - distancesBombShelters[midIndex - 1]) < diffNum)
        {
            midIndex -= 1;
            diffNum = abs(num - distancesBombShelters[midIndex - 1]);
            diff ++;
        }
        if(midIndex + diff < countOfBombShelters - 1 && abs(num - distancesBombShelters[midIndex + 1 + diff]) < diffNum)
        {
            midIndex += 1 + diff;
//            diffNum = abs(num - distancesBombShelters[midIndex + 1 + diff]);
        }
        outf << indexesB[midIndex][1] + 1 << " ";
    }

    outf.close();

    // Бинарный поиск.
    // Сортировка слиянием.
    // Cats ругается непонятно на что (на стационарном компиляторе всё работает)
}
