#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    int iCountOfNums; // Количество чисел
    int iCountOfComands; // Количество команд
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iCountOfNums;

    vector <int> iMass; // Массив чисел
    int iSum = 0;

    for (int i = 0; i < iCountOfNums; i++)
    {
        int iNum;
        inf >> iNum;
        iSum += iNum;
        iMass.push_back(iSum);
    }

    inf >> iCountOfComands;
    int iC = 1;

    for (int i = 0; i < iCountOfComands; i++)
    {
        int iLeft; // левый индекс
        int iRight; // правый индекс
        inf >> iLeft >> iRight;
        iLeft -= 1; iRight -= 1;
        int iRemoval = iLeft - 1; // индекс убираемого элемента

        iSum = iMass[iRight] - ((iRemoval < 0) ? 0 : iMass[iRemoval]);
        outf << iSum;
        cout << iSum;
        if (iC != iCountOfComands)
        {
            outf << " ";
            cout << " ";
        }
    }
}