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
    if (iSubCount >= 4 || iCount == 0) // iCount - костыль для VS
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

    int imNum[(10000 / 4) + 1];
    // В массиве по 4 элемента
    int iCount = 0;
    int iSubCount = -1;
    int iLength = 0;

    MassCreator(imNum, '\n', iCount, iSubCount, iLength);
    iLength += 1;
    imNum[0] = iCount; // Номер последнего элемента

    ifstream inf("input.txt");
    inf.seekg(iLength, ios::cur);
    int iNumShort;
    inf >> iNumShort;
    inf.close();

    bool bStateOfFirstNum = true;
    int iRemn = 0;

    for (int iIndex = imNum[0]; iIndex > 0; iIndex -= 1)
    {
        iRemn = 10000 * iRemn + imNum[iIndex];
        imNum[iIndex] = iRemn / iNumShort;
        if (imNum[iIndex] == 0 && bStateOfFirstNum)
        {
            imNum[0] -= 1;
        }
        else
        {
            bStateOfFirstNum = false;
        }
        iRemn %= iNumShort;
    }
    for (int iIndex = imNum[0]; iIndex > 0; iIndex -= 1)
    {
        outf << imNum[iIndex]; // Вылезает ненужный 0
        cout << imNum[iIndex];
    }
    outf << endl << iRemn;
    cout << endl << iRemn;
}