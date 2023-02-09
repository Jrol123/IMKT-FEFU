#include <iostream>
#include <string>
using namespace std;

int main()
{
    int iNum, iNumOfNotNulled;
    cin >> iNum >> iNumOfNotNulled;

    int iMask = (1 << (iNumOfNotNulled)) - 1;
    //cout << iMask << endl;

    cout << (iMask & iNum);
}