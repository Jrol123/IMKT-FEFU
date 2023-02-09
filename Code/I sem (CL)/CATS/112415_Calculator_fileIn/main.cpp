#include <iostream>
using namespace std;

int Grower(char &cSym)
{
    cSym = cin.get();
    int iSym = int(cSym) - 48;
    int iNum = 0;

    while (0 <= iSym && iSym <= 9)
    {
        iNum *= 10;
        iNum += iSym;

        cSym = cin.get();
        iSym = int(cSym) - 48;
    }
    return iNum;
} // Ввод числа

int main()
{
    const int iLength = 5;
    int iNum = 0;
    char cSym;

    iNum = Grower(cSym);

    while (cSym != '\n')
    {
        if (cSym == '+')
        {
            iNum += Grower(cSym);
        }
        else
        {
            iNum -= Grower(cSym);
        }
        //iNum = Merger(iNum, Grower(cSym), cSym);
    }
    cout << iNum;
}