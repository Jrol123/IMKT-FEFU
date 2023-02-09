#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

int partition(int list[], int start, int end)
{
    int pivot = list[end];

    int pIndex = start;

    for (int i = start; i < end; i++)
    {
        if (list[i] <= pivot)
        {
            swap(list[i], list[pIndex]);
            pIndex++;
        }
    }

    swap (list[pIndex], list[end]);
    return pIndex;
}

void quicksort(int list[], int start, int end)
{
    if (start >= end)
    {
        return;
    }

    int pivot = partition(list, start, end);

    quicksort(list, start, pivot - 1);

    quicksort(list, pivot + 1, end);
}


int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n;
    fin >> n;
    int list[n];
    for(int i = 0; i < n; i++){
        fin >> list[i];
    }
    int k = sizeof(list)/sizeof(list[0]);

    quicksort(list, 0, k - 1);

    for (int i = 0; i < k; i++) {
        fout << list[i] << " ";
    }

    return 0;
}