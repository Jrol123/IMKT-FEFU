#include <iostream>
using namespace std;

int main()
{
    int iHeight, iUpDay, iDownNight;
    cin >> iHeight >> iUpDay >> iDownNight;

    int iCountOfDays = (iHeight - iDownNight - 1) / (iUpDay - iDownNight) + 1; // h - a + a - b - 1 (для правильного деления)

    cout << iCountOfDays;
}
