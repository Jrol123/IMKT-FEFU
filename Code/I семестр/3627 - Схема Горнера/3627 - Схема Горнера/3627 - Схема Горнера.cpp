#include <iostream>
using namespace std;

int main()
{
    int iCountOfNums; // Количество цифр
    float fX;
    cin >> iCountOfNums;

    cin >> fX;

    float fNum;
    cin >> fNum;

    for (int i = 0; i < iCountOfNums; i++)
    {
        float fSubNum;
        cin >> fSubNum;

        fNum *= fX;
        fNum += fSubNum;
    }
    cout << fNum;
}