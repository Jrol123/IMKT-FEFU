#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
// \n делит строки
// \377 означает end of file

// Цикл, пока не найден \n или \377

void MassCreator(int(&iNumMass)[(10000 / 4) + 1], char cBreaker, int& iCount, int& iSubCount, int& iLength)
{
    ifstream inf("input.txt");

    inf.seekg(iLength, ios::cur);

    char cChar = inf.get();
    iLength += 1;

    if (cChar != cBreaker)
    {
        MassCreator(iNumMass, cBreaker, iCount, iSubCount, iLength);
    }
    else
    {
        inf.close();
        return void();
    }

    iSubCount += 1;
    if (iSubCount >= 4 || iCount == 0)
    {
        iCount += 1;
        iSubCount = 0;
        iNumMass[iCount] = 0; // Это костыль. На CLion он не нужен.
    }

    int t = pow(10, iSubCount);
    iNumMass[iCount] = iNumMass[iCount] + (cChar - 48) * t;

    inf.close();
}

int main()
{
    ofstream outf("output.txt");

    int imNum1[(10000 / 4) + 1];
    int imNum2[(10000 / 4) + 1];
    // В массиве по 4 элемента
    int iCount = 0;
    int iSubCount = -1;
    int iLength = 0;

    MassCreator(imNum1, '\n', iCount, iSubCount, iLength);
    iLength += 1;
    imNum1[0] = iCount; // Номер последнего элемента
    iCount = 0;
    iSubCount = -1;

    MassCreator(imNum2, '\377', iCount, iSubCount, iLength); // Может быть надо заменить \n на \377
    imNum2[0] = iCount;


    for (int iIndex = 1; iIndex <= imNum1[0]; iIndex++)
    {
        int iSum = imNum1[iIndex] + imNum2[iIndex];
        imNum1[iIndex] = iSum % 10000;
        imNum1[iIndex + 1] += iSum / 10000;
    } // Суммирование идёт слева направо
    for (int iIndex = imNum1[0]; iIndex > 0; iIndex -= 1)
    {
        outf << imNum1[iIndex];
        cout << imNum1[iIndex];
    }
}