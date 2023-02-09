#include <iostream>
using namespace std;

void MassReverser(int iCountOfNums)
{
    iCountOfNums -= 1;
    if (iCountOfNums > 0)
    {
        int iNum;
        cin >> iNum;
        MassReverser(iCountOfNums);
        cout << iNum << " ";
    }
    else
    {
        int iNum;
        cin >> iNum;
        cout << iNum << " ";
    }
}

int main()
{
    int iCountOfNums; // Количество цифр
    cin >> iCountOfNums;
    iCountOfNums -= 1;
    int iNum;
    cin >> iNum;
    if (iCountOfNums > 0)
    {
        MassReverser(iCountOfNums);
    }
    cout << iNum;
}