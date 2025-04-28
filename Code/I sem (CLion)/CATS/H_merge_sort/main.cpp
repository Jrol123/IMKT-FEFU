#include <iostream>
#include <fstream>
using namespace std;

void merge(int arr[], int start, int end, int mid, int L)
{
    int mergedArr[L];
//    int mergedIndexes[L];
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
//            mergedIndexes[k] = indexes[i];
            k++;
            i++;
        }
        else
        {
            // cout << arr[i] << " | " << arr[j] << endl;
            mergedArr[k] = arr[j];
//            mergedIndexes[k] = indexes[j];

            k++;
            j++;
        }
    }

    while (i <= mid)
    {
        mergedArr[k] = arr[i];
//        mergedIndexes[k] = indexes[i];
        k++;
        i++;
    }

    while (j <= end)
    {
        mergedArr[k] = arr[j];
//        mergedIndexes[k] = indexes[j];
        k++;
        j++;
    }

    for (i = start; i < k; i++)
    {
        arr[i] = mergedArr[i];
//        indexes[i] = mergedIndexes[i];
    }
}

void mergeSort(int arr[], int start, int end, int L)
{
    int mid;
    if (start < end)
    {
        mid = (start + end) / 2;
        mergeSort(arr, start, mid, L);
        mergeSort(arr, mid + 1, end, L);
        merge(arr, start, end, mid, L);
    }
}

int main()
{
    ifstream inf ("input.txt");

    int countOfNums; inf >> countOfNums;
    int massNums [countOfNums];
    for(int i = 0; i < countOfNums; i++)
    {
        int num; inf >> num;
        massNums[i] = num;
    }
    inf.close();

    mergeSort(massNums, 0, countOfNums - 1, countOfNums);

    ofstream outf ("output.txt");
    for(int i = 0; i < countOfNums; i++)
    {
        outf << massNums[i] << " ";
    }
    outf.close();
}
