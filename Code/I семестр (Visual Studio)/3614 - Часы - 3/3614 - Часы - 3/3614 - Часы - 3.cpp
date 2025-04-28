#include <iostream>
using namespace std;
//Максимум - 12 часов
//180 = 21 600
//90 = 10 800
//1 = 120 (2)
int main()
{
    double dAlpha;
    const double dGrad = 120;
    cin >> dAlpha;

    int iFullSec = dAlpha * dGrad;
    int iHour = iFullSec / 3600;
    iFullSec %= 3600;
    int iMinutes = iFullSec / 60;
    iFullSec %= 60;

    cout << iHour << " " << iMinutes << " " << iFullSec;
}