#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;
/*
 * Положение точки относительно линии.
 */

int main()
{
    int xa, ya, xb, yb, xc, yc;
    cin >> xa >> ya >> xb >> yb >> xc >> yc;

    int res = (xb - xa) * (yc - ya) - (yb - ya) * (xc - xa);
    if (res > 0)
        cout << "LEFT" << endl;
    else if (res < 0)
        cout << "RIGHT" << endl;
    else
        cout << "BOTH" << endl;
}