#include <iostream>
using namespace std;

int main()
{
    int iNumOfYear;
    cin >> iNumOfYear;

    string sState = "NO";
    if (((iNumOfYear % 100 != 0) && (iNumOfYear % 4 == 0)) || (iNumOfYear % 400 == 0))
    {
        sState = "YES";
    }// с таким же успехом можно сравнивать побитово, маской, разницы никакой
    /*
    if (!((iNumOfYear % 100 == 0) && (iNumOfYear % 4 != 0)) && (iNumOfYear % 4 == 0))
    {
        sState = "YES";
    }
    */

    cout << sState;
}
