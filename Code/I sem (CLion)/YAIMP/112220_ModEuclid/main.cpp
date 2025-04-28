#include <iostream>
using namespace std;

int main()
{
    int iNum1, iNum2;
    cin >> iNum1 >> iNum2;
    int iMax = max(iNum1, iNum2);
    int iMin = min(iNum1, iNum2);
    int iCountSteps = 0;

    do
    {
        iCountSteps += 1;
        iNum1 = iMax % iMin, iNum2 = iMin;
        iMax = iNum2;
        iMin = iNum1;
    } while (iMin > 0);

    cout << iMax << " " << iCountSteps;
}