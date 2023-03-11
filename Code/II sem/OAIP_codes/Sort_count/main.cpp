#include <iostream>
#include <fstream>
using namespace std;

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
}