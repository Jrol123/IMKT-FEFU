#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;


void merge(float arr[], int indexes[], int start, int end, int mid, int L);

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


int main() {
    int N;
    ifstream inf ("input.txt");
    inf >> N;

    float heights[N];
    char names[N][255];
    int indexes[N];

    for (int i = 0; i < N; i++)
    {
        inf >> heights[i] >> names[i];
        indexes[i] = i;
    }

    inf.close();

    mergeSort(heights, indexes, 0, N - 1, N);

    FILE *f2 = fopen("output.txt", "w");


    for (int i = 0; i < N; i++)
    {
        fprintf(f2, "%s\n", names[indexes[i]]);
    }

    fclose(f2);

    return 0;
}
