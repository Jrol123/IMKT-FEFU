//#include <iostream>
#include <fstream>
=======
#include <iostream>
>>>>>>> Stashed changes
using namespace std;

void sort_count (int mass[], int len)
{
//    int min = INT_MAX;
//    int max = INT_MIN;
    int subLen = len * 10;
    int subMass [subLen];
    fill(subMass, subMass + subLen, 0);

    for (int i = 0; i < len; ++i)
    {
        subMass[mass[i]] += 1;
    }

    int pos = 0;

    for (int num = 0; num < subLen; ++num)
    {
        for (int i = 0; i < subMass[num]; i++)
        {
            mass[pos] = num;
            pos++;
        }
    }
}

int main()
{
    int mass [] {3, 2, 5, 11, 3};
    sort_count(mass, 5);
    cout << mass[1] << " " << mass[2];
}