#include <iostream>
#include <stdio.h>
//#include <fstream>
#include <cmath>
using namespace std;

FILE * aF = fopen ("input.txt","r");

void MassCreator(int (&iNumMass)[(10000 / 4) +1], char cBreaker, int& iCount,int &iSubCount, int &iLength)
{
    char cChar;
    fscanf(aF, "%c", &cChar);
    iLength += 1;

    if (cChar != cBreaker)
    {
        MassCreator(iNumMass, cBreaker, iCount, iSubCount,iLength);
    }
    else
    {
        return void();
    }

    iSubCount += 1;
    if (iSubCount >= 4)
    {
        iCount += 1;
        iSubCount = 0;
    }
    // Необходимо поменять систему умножения на 10
    int t = pow(10, iSubCount);
    iNumMass[iCount] = iNumMass[iCount] + (cChar - 48) * t;
}

int main()
{
    int iMass1[(10000 / 4) +1] {0};
    int iMass2[(10000 / 4) +1] {0};

    int iCount = 1;
    int iSubCount = -1;
    int iLength = 0;

    MassCreator(iMass1, '\n', iCount, iSubCount, iLength);
    iLength += 1;
    iMass1[0] = iCount; // Номер последнего элемента
    iCount = 1;
    iSubCount = -1;

    MassCreator(iMass2, '\000', iCount, iSubCount, iLength);
    iMass2[0] = iCount;

    int iMaxIndex = max(iMass1[0], iMass2[0]);
    bool stateOfNegative = false;
    //int iIndexOfLastNum = iMaxIndex;

    for(int iIndex = iMaxIndex; iIndex >= 1; iIndex--)
    {
        int iNum1 = iMass1[iIndex];
        int iNum2 = iMass2[iIndex];

        if (iNum2 > iNum1 && !stateOfNegative)
        {
            if (iIndex + 1 <= iMaxIndex)
            {
                for (int iSubIndex = iIndex + 1; iSubIndex <= iMaxIndex; iSubIndex ++)
                {
                    int iNum3 = iMass1[iSubIndex];
                    if (iNum3 == 0)
                    {
                        iMass1[iSubIndex] = 9999;
                    }
                    else if (iSubIndex <= iMaxIndex)
                    {
                        iMass1[iSubIndex] -= 1;
                        if (iMass1[iSubIndex] == 0 && iSubIndex == iMaxIndex)
                        {
                            iMaxIndex -= 1;
                            iMass1[iIndex] = 10000 - iNum2 + iNum1;
                        }
                        // Обработать минус значение
                    }
                    else
                    {
                        stateOfNegative = true;
                        iMass1[iIndex] = iNum2 - iNum1;
                    }
                }
            }
            else
            {
                stateOfNegative = true;
                iMass1[iIndex] = iNum2 - iNum1;
            }
        }
        else if(stateOfNegative)
        {
            iMass1[iIndex] = iNum2 - iNum1;
        }
        else
        {
            iMass1[iIndex] -= iNum2;
            if (iMass1[iIndex] == 0)
            {
                iMaxIndex -= 1;
            }
        }
    }
    if (iMaxIndex < iMass1[0])
    {
        iMass1[0] = iMaxIndex;
    }
    FILE *oF = fopen("output.txt", "w");
    //ofstream outf ("output.txt");
    for (int iIndex = iMass1[0]; iIndex > 0; iIndex -= 1)
    {
        int iNum = iMass1[iIndex];
        string sFinal = "";
        bool bStateOfZero = (iNum / 10000 == 0);
        if (iIndex == iMass1[0] && stateOfNegative)
        {
            sFinal += '-';
        }
        for(int i = 4; i > 0; i --)
        {
            int t = pow(10, i - 1);
            int iStrNum = iNum / t; // Для корректного вывода
            if (!(iStrNum == 0 && bStateOfZero && iIndex == iMass1[0])) // Условие для не-вывода нулей перед числом
            {
                sFinal = sFinal + to_string(iStrNum);
                iNum -= iStrNum * t;
                bStateOfZero = false;
            }
        }
        if (sFinal == "")
        {
            sFinal = "0";
        }

        //outf << sFinal;
        fprintf(oF,"%s", sFinal.c_str());
        cout << sFinal;
    } // Вывод с начала четвёрки
    // Если ячейка > ячейки: поиск следующей ячейки. 0-ли превращаются в 9999
}
