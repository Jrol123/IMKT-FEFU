#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
// \n делит строки
// \377 означает end of file

// Цикл, пока не найден \n или \377

void MassCreator(int(&iSubMass1)[(10000 / 2 / 4) + 1 + 2 + 6250], int(&iSubMass2)[(10000 / 2 / 4) + 1 + 2 + 6250], char cBreaker, int& iCount, int& iSubCount, int& iLength, int& iLengthOfLongNum, int & iNowLength, int& iNowCount, bool& bStateOfMass)
{
    ifstream inf("input.txt");

    inf.seekg(iLength, ios::cur);

    char cChar = inf.get();

    iLength += 1;

    if (cChar != cBreaker)
    {
        iLengthOfLongNum += 1;
        MassCreator(iSubMass1, iSubMass2, cBreaker, iCount, iSubCount, iLength, iLengthOfLongNum, iNowLength, iNowCount, bStateOfMass);
    }
    else
    {
        inf.close();
        return void();
    }

    iSubCount += 1;
    iNowLength += 1;
    if (iSubCount >= 4 || iCount == 0) // iCount - костыль для VS
    {
        iCount += 1;
        iSubCount = 0;
//      iNumMass[iCount] = 0; // Это костыль. На CLion он не нужен.
    }
    if (iNowLength > ceil((double)iLengthOfLongNum / 2) && !bStateOfMass)
    {
        iSubMass1[0] = iCount; // Длина первого подмассива
        iNowLength = 0;
        bStateOfMass = true;
    }

    if (!bStateOfMass)
    {
        int t = pow(10, iSubCount);
        iSubMass1[iCount] = iSubMass1[iCount] + (cChar - 48) * t;
        if (iLengthOfLongNum == 1)
        {
            iSubMass1[0] = 1;
            iNowCount += 1;
        }
    }
    else
    {
        if (iNowLength >= 4 || iNowCount == 0) // iNowCount - костыль для VS
        {
            iNowCount += 1;
            iNowLength = 0;
//          iSubMass2[iNowCount] = 0; // Это костыль. На CLion он не нужен.
        }
        int t = pow(10, iNowLength);
        iSubMass2[iNowCount] = iSubMass2[iNowCount] + (cChar - 48) * t;
    }

    inf.close();
}

void MassShift (int (&iMass)[(10000 / 2 / 4) + 1 + 2 + 6250], int iCountOfShift)
{
    for(int iIndex = iMass[0]; iIndex >= 1; iIndex --)
    {
        iMass[iIndex + iCountOfShift] = iMass[iIndex];
        iMass[iIndex] = 0;
    }
    iMass[0] += iCountOfShift;
}

void MassMul(int (&iMass1)[(10000 / 2 / 4) + 1 + 2 + 6250], int (&iMass2)[(10000 / 2 / 4) + 1 + 2 + 6250], int(&iMassMul)[(10000 / 2 / 4) + 1 + 2 + 6250])
{
    for (int iIndex = 1; iIndex <= iMass1[0]; iIndex += 1)
    {
        int iNum = iMass1[iIndex];
        for (int iSubIndex = 1; iSubIndex <= iMass2[0]; iSubIndex += 1)
        {
            //int t = pow(10, iIndex - 1);
            int iMul = iNum * iMass2[iSubIndex]; // Возможно, нужно дописать умножение на t
            iMassMul[iSubIndex] += iMul % 10000;
            iMassMul[iSubIndex + 1] += iMul / 10000;
        }
    }// Попытка реализовать умножение в пре-цикле
    iMassMul[0] = (iMassMul[iMass1[0] + 1] > 0) ? iMass1[0] + 1 : iMass1[0];
}

void MassMul(int (&iMass)[(10000 / 2 / 4) + 1 + 2 + 6250], int iCountOfZeros)
{
    int iMoveCount = iCountOfZeros / 4;
    int iRestCount = iCountOfZeros % 4;

    if (iMoveCount != 0)
    {
        MassShift(iMass, iMoveCount);
    }
    if (iRestCount != 0)
    {
        int t = pow(10, iRestCount);

        for (int iIndex = iMass[0]; iIndex >= 1; iIndex --)
        {
            int iNum = iMass[iIndex];
            if (iNum != 0)
            {
                iMass[iIndex + 1] += iNum / (10000 / t);
                iMass[iIndex] = (iNum % (10000 / t)) * t;
            }
        }
        iMass[0] = (iMass[iMass[0]+ 1] > 0) ? iMass[0] + 1 : iMass[0];
    }
}

void MassSum(int (&iMass1)[(10000 / 2 / 4) + 1 + 2 + 6250], int (&iMass2)[(10000 / 2 / 4) + 1 + 2 + 6250])
{
    int iMaxIndex = (iMass1[0], iMass2[0]);
    for(int iIndex = 1; iIndex <= iMaxIndex; iIndex++)
    {
        int iSum = iMass1[iIndex] + iMass2[iIndex];
        iMass1[iIndex] = iSum % 10000;
        iMass1[iIndex + 1] += iSum / 10000;
    } // Суммирование идёт слева направо
    iMass1[0] = (iMass1[iMaxIndex+ 1] > 0) ? iMaxIndex + 1 : iMaxIndex;
}

void MassSub(int (&iMass1)[(10000 / 2 / 4) + 1 + 2 + 6250], int (&iMass2)[(10000 / 2 / 4) + 1 + 2 + 6250])
{
    int iMaxIndex = max(iMass1[0], iMass2[0]);
    for(int iIndex = 1; iIndex <= iMaxIndex; iIndex++)
    {
        int iNum1 = iMass1[iIndex];
        int iNum2 = iMass2[iIndex];

        if (iNum2 > iNum1)
        {
            for (int iSubIndex = iIndex + 1; iSubIndex <= iMaxIndex; iSubIndex ++)
            {
                int iNum3 = iMass1[iSubIndex];
                if (iNum3 == 0)
                {
                    iMass1[iSubIndex] = 9999;
                }
                else
                {
                    iMass1[iSubIndex] -= 1;
                    if (iMass1[iSubIndex] == 0 && iSubIndex == iMaxIndex)
                    {
                        iMaxIndex -= 1;
                    }
                }
            }
            iMass1[iIndex] = 10000 - iNum2 + iNum1;
        }
        else
        {
            iMass1[iIndex] -= iNum2;
        }
    }
    if (iMaxIndex < iMass1[0])
    {
        iMass1[0] = iMaxIndex;
    }
    // Если ячейка > ячейки: поиск следующей ячейки. 0-ли превращаются в 9999
}

int main()
{
    ofstream outf("output.txt");

    int imNum1_sub1[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Правая реальная часть
    int imNum1_sub2[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Левая реальная часть

    int imNum2_sub1[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Множитель правых частей
    int imNum2_sub2[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Множитель левых частей

    int imNum_sub3[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Костыль

    int imNumMul_sub1[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Левая
    int imNumMul_sub2[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Правая
    int imNumMul_sub3[(10000 / 2 / 4) + 1 + 2 + 6250] {0}; // Результаты
    // +1 - Резерв для переполнения

    int iLength1;
    int iLength2;

    int iCount = 0;
    int iSubCount = -1;
    int iLength = 0;
    int iLengthOfLongNum = 0;
    int iNowLength = 0;
    int iNowCount = 0;
    bool bState = false;

    MassCreator( imNum1_sub1, imNum1_sub2, '\n', iCount, iSubCount, iLength, iLengthOfLongNum, iNowLength, iNowCount, bState);
    imNum1_sub2[0] = iNowCount;
    iLength1 = iLengthOfLongNum;
    iLength += 1;
    iCount = 0;
    iSubCount = -1;
    iLengthOfLongNum = 0;
    iNowLength = 0;
    iNowCount = 0;
    bState = false;

    MassCreator( imNum2_sub1, imNum2_sub2, '\377', iCount, iSubCount, iLength, iLengthOfLongNum, iNowLength, iNowCount, bState);
    imNum2_sub2[0] = iNowCount;
    iLength2 = iLengthOfLongNum;

    MassMul(imNum1_sub1, imNum2_sub1, imNumMul_sub1); // Умножение правой части на правую
    MassMul(imNum1_sub2, imNum2_sub2, imNumMul_sub2); // Умножение левой части на левую

    MassSum(imNum1_sub1, imNum1_sub2); // Суммирование первого числа
    MassSum(imNum2_sub1, imNum2_sub2); // Суммирование второго числа

    MassMul(imNum1_sub1, imNum2_sub1, imNumMul_sub3); // Умножение сумм первого и второго чисел

    for(int i = 0; i <= imNumMul_sub1[0]; i++)
    {
        imNum_sub3[i] = imNumMul_sub1[i];
    }

    MassSum(imNum_sub3, imNumMul_sub2); // Суммирование результатов произведения

    MassSub(imNumMul_sub3, imNum_sub3); // Вычитание суммы произведения из произведения сумм первого и второго чисел


    int iMaxRange = ceil((double)max(iLength1, iLength2) / 2); // База

    MassMul(imNumMul_sub2, iMaxRange * 2); // Умножение произведения левых половинок на базу в квадрате
    MassMul(imNumMul_sub3, iMaxRange * 1); // Умножение разницы на базу

    MassSum(imNumMul_sub2, imNumMul_sub3);

    MassSum(imNumMul_sub1, imNumMul_sub2);

    for (int iIndex = imNumMul_sub1[0]; iIndex > 0; iIndex -= 1)
    {
        int iNum = imNumMul_sub1[iIndex];
        string sFinal = "";
        bool bStateOfZero = (iNum / 10000 == 0);
        for(int i = 4; i > 0; i --)
        {
            int t = pow(10, i - 1);
            int iStrNum = iNum / t; // Для корректного вывода
            if (!(iStrNum == 0 && bStateOfZero && iIndex == imNumMul_sub1[0])) // Условие для не-вывода нулей перед числом
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
        outf << sFinal;
        cout << sFinal;
    } // Вывод с начала четвёрки
    // Работает, но не полностью. Необходимо отладить
    // Не работает с примером Влада. Также не работает с 10 при числе длинной более 3-х
    // Поэксперементировать с 0-ми
}