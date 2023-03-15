//#include <fstream>
#include <iostream>
using namespace std;

void sort_count (int mass[], int len)
{
    int minNum = INT_MAX;
    int maxNum = INT_MIN;
    for (int i = 0; i < len; ++i)
    {
        minNum = min(mass[i], minNum);
        maxNum = max(mass[i], maxNum);
    }

    int subLen = maxNum - minNum + 1;
    int subMass [subLen];
    fill(subMass, subMass + subLen, 0);

    for (int i = 0; i < len; ++i)
    {
        subMass[mass[i] - minNum] += 1;
    }

    int pos = 0;

    for (int num = 0; num < subLen; ++num)
    {
        for (int i = 0; i < subMass[num]; i++)
        {
            mass[pos] = num + minNum;
            pos++;
        }
    }
}

int main()
{
    int mass [] {5,2,3,1};
    sort_count(mass, 4);
    cout << mass[0] << " " << mass[1] << " " << mass[2];
}