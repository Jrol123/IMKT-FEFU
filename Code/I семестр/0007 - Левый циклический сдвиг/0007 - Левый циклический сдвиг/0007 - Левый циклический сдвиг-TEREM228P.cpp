#include <iostream>
#include <cmath>
using namespace std;
// Выполнить левый циклический сдвиг заданного целого числа

int main1(int iNum, int iSizeOfNum, int iCountOfMoves)
{
    int iNumOfContr = 1 << iSizeOfNum; // *значение* крайнего бита (будущего)
    int iNumOfPreContr = 1 << (iSizeOfNum - 1); // *значение* крайнего бита (настоящего)
    cout << sizeof(iNum) << "  " << iSizeOfNum << "  " << iNumOfContr << "  " << iNumOfPreContr << endl << endl;
    for (int i = 1; i <= iCountOfMoves; i++)
    {
        /*
        int iPlus = ((iNum << 1) / (iNumOfContr); // крайний левый бит (0 или 1)
        iNum = ((iNum << 1) % iNumOfContr) + iPlus;
        //cout << "I" << (iNum << 1) << " " << double(iNumOfContr / iNum) << " " << 10/8 << endl;
        */
        
        int iPlus = ((iNum) / (iNumOfPreContr)); // крайний левый бит (0 или 1)
        int iNumIf = ((iNum & (~iNumOfPreContr)) << 1) + iPlus;
        iNum = (((iNum) % iNumOfPreContr)<<1) + iPlus;
        
        /*
        int iPlus = iNum / iNumOfContr; // крайний левый бит (настоящий) (0 или 1)
        iNum = ((iNum & (~iNumOfPreContr)) << 1) + iPlus; // убирание крайнего левого числа -> сдвиг -> добавление бывшего левого бита
        */
        
        cout << i << "  " << iPlus << " " << iNum << " " << iNumIf << endl;
    }
    return iNum;
}

int main2(int iNum, int iSizeOfNum, int iCountOfMoves)
{
    if (iNum > 0)
    {

    }
    return ((iNum << iCountOfMoves) | (iNum >> (32 - iCountOfMoves))); //31 + знак
    // При iCM > 32, сдвиг на отриц. число даёт сдвиг на положит. число
    // сохраняется знак
}

int main()
{
    int iStat, iNum, iCountOfMoves;
    cout << "Enter the number of method: ";
    cin >> iStat;
    cout << endl << "Enter the Number and Count of moves: ";
    cin >> iNum >> iCountOfMoves;
    cout << endl;

    int iSizeOfNum = (sizeof(iNum) - 1); // длина в битах (до последнего значимого бита) (почему мне приходится писать -1?)

    if (iStat % 2 != 0)
    {
        cout << endl << main1(iNum, iSizeOfNum, iCountOfMoves);
    }
    else
    {
        cout << endl << main2(iNum, iSizeOfNum, iCountOfMoves);
    }
}
