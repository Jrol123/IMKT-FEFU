//#include <fstream>
#include <iostream>
using namespace std;

<<<<<<< Updated upstream
void sort_count (int mass[], int len)
{
    int minNum = INT_MAX;
    int maxNum = INT_MIN;
    for (int i = 0; i < len; ++i)
    {
        minNum = min(mass[i], minNum);
        maxNum = max(mass[i], maxNum);
    }

    int subLen = maxNum - minNum;
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
    int mass [] {3, 2, 5, 11, 3};
    sort_count(mass, 5);
    cout << mass[1] << " " << mass[2];
=======
<<<<<<< Updated upstream
int main()
{
    ifstream inf ("input.txt");
    int minNum, maxNum; // Края определяемой зоны
    inf >> minNum >> maxNum;

    int mass [maxNum - minNum + 1];
    fill(mass, mass + (maxNum - minNum) + 1, 0);

    int num;
    inf >> num;

    while (inf.get() != '\377')
    {
        mass[num - minNum] ++;
        inf >> num;
    }
    mass[num - minNum] ++;
    inf.close();

    ofstream outf("output.txt");
    for (int i = 0; i <= maxNum - minNum; ++i)
    {
        if (mass[i] != 0)
        {
            outf << i + minNum << " " << mass[i] << endl;
        }
    }

    outf.close();
=======
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
    cout << mass[1] << " " << mass[2];
>>>>>>> Stashed changes
>>>>>>> Stashed changes
}