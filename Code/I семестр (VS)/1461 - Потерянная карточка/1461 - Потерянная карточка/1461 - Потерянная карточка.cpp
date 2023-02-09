#include <iostream>
#include <vector>
using namespace std;

void iPrevAndFuture(int iIndex, int iNum, vector <int> iMass, int &iCountOfTheSame, int iCountOfDeleted)
{
    const int iSubIndex = iIndex - iCountOfTheSame - iCountOfDeleted - 1 - 1; // Поиск индекса -2 го элемента 
    iCountOfTheSame = 1;
    // в iSubIndex мы пишем iCountOfDeleted т.к. это "пустота", образовавшаяся после удаления шаров, которую необходимо учитывать
    if (iSubIndex >= 0)
    {
        int iSubPrevNum = iMass[iSubIndex];
        int iSubNum = iMass[iSubIndex + 1];
        if (iNum == iSubNum)
        {
            iCountOfTheSame += 1;
            if (iSubNum == iSubPrevNum)
            {
                iCountOfTheSame += 1;
            }
        }
    } // если -2 элемент существует
    else if (iSubIndex + 1 == 0)
    {
        int iSubNum = iMass[iSubIndex + 1];
        if (iNum == iSubNum)
        {
            iCountOfTheSame += 1;
        }
    } // если -1 элемент существует
}

int main()
{
    int iCountOfBalls; // Количество шаров
    const int icCountOfCanDelete = 3; // Минимальное количество шаров, которое можно удалить
    int iCountOfDeleted = 0; // Кол-во удалённых шаров
    cin >> iCountOfBalls;

    vector <int> iMass;
    int iCountOfTheSame = 1;
    for (int i = 0; i < iCountOfBalls; i++)
    {
        int iNum = 0;
        cin >> iNum;
        iMass.push_back(iNum);
    }
    int iPrevNum = iMass[0];
    for (int iIndex = 1; iIndex <= (iCountOfBalls - 1); iIndex ++)
    {
        int iNum = iMass[iIndex];
        if (iNum == iPrevNum)
        {
            iCountOfTheSame += 1;
        }
        else
        {
            if (iCountOfTheSame >= icCountOfCanDelete)
            {
                iCountOfDeleted += iCountOfTheSame;
                iPrevAndFuture(iIndex, iNum, iMass, iCountOfTheSame, iCountOfDeleted - iCountOfTheSame);
            }
            else
            {
                iCountOfTheSame = 1;
            }
        }// Всё начинается с одной главной последовательности...
        iPrevNum = iNum;
    }
    if (iCountOfTheSame >= icCountOfCanDelete)
    {
        iCountOfDeleted += iCountOfTheSame;
    }
    cout << iCountOfDeleted;
}