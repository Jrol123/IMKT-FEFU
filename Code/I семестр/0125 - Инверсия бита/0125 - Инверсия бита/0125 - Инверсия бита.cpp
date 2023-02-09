#include <iostream>

using namespace std;

int main()
{
    int iNum, iNumOfReversed;
    cin >> iNum >> iNumOfReversed;

    int iMask = 1 << iNumOfReversed;

    cout << (iNum ^ iMask) << endl << (iNum & ~iMask);
}
