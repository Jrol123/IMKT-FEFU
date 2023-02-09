// h:mm:ss

#include <iostream>
using namespace std;

int main()
{
    int iFullTime, iHr = 0, iMn = 0, iSc = 0;
    cin >> iFullTime;

    iHr = (iFullTime / 3600) % 24;
    iFullTime %= 3600;
    iMn = iFullTime / 60;
    iSc = iFullTime % 60;

    cout << iHr << ':' << iMn / 10 << iMn % 10 << ':' << iSc / 10 << iSc % 10;
}
