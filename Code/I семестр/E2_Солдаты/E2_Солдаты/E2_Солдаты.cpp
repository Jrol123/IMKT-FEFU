#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;


void merge(float arr[], int indexes[], int start, int end, int mid, int L)
{
    float mergedArr[L];
    int mergedIndexes[L];
    int i, j, k;
    i = start;
    k = start;
    j = mid + 1;

    while (i <= mid && j <= end)
    {
        if (arr[i] >= arr[j])
        {
            // cout << arr[i] << " " << arr[j] << endl;
            mergedArr[k] = arr[i];
            mergedIndexes[k] = indexes[i];
            k++;
            i++;
        }
        else
        {
            // cout << arr[i] << " | " << arr[j] << endl;
            mergedArr[k] = arr[j];
            mergedIndexes[k] = indexes[j];

            k++;
            j++;
        }
    }

    while (i <= mid)
    {
        mergedArr[k] = arr[i];
        mergedIndexes[k] = indexes[i];
        k++;
        i++;
    }

    while (j <= end)
    {
        mergedArr[k] = arr[j];
        mergedIndexes[k] = indexes[j];
        k++;
        j++;
    }

    for (i = start; i < k; i++)
    {
        arr[i] = mergedArr[i];
        indexes[i] = mergedIndexes[i];
    }
}

void mergeSort(float arr[], int indexes[], int start, int end, int L)
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

int main()
{
    ifstream inf("input.txt");
    int countOfSoldiers; inf >> countOfSoldiers;

    float heights[countOfSoldiers];
    char names[countOfSoldiers][255];
    int a[countOfSoldiers];

    for (int i = 0; i < countOfSoldiers; i++)
    {
        inf >> heights[i] >> names[i];
        a[i] = i;
    }
    inf.close();

    mergeSort(heights, a, 0, countOfSoldiers - 1, countOfSoldiers);

    ofstream outf("output.txt");
    for (int i = 0; i < countOfSoldiers; i++)
    {
        outf << names[a[i]];
    }

    outf.close();
}
