#include <iostream>
using namespace std; //73

int main()
{
    int iCountOfElem;
    cin >> iCountOfElem;
    int iPrevNum, iNum;
    int iCount = 1;
    cin >> iPrevNum;

    for (int i = 1; i < iCountOfElem; i++)
    {
        cin >> iNum;
        if (iNum != iPrevNum)
        {
            iCount += 1;
        }
        iPrevNum = iNum;
    }
    cout << iCount;
}