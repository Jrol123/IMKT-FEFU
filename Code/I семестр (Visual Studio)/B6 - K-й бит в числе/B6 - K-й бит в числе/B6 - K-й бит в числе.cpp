#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
// как учесть 100-й бит числа?
int main()
{
    long long iNum; // число
    long long iMask; // Маска
    long long iCritMask; // Маска * 2
    int iIndexOfBit; // номер бита, чьё значение необходимо узнать
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iNum >> iIndexOfBit;
    cout << iNum << " " << iIndexOfBit << endl << endl;

    if (iIndexOfBit > 31)
    {
        cout << 0 << endl;
        outf << 0;
    } // выход за int
    else
    {
        iCritMask = pow(2, iIndexOfBit + 1);
        iMask = pow(2, iIndexOfBit);
        iCritMask = iNum % iCritMask;
        cout << (((iCritMask - iMask) >= 0) ? 1 : 0) << endl;
        outf << (((iCritMask - iMask) >= 0) ? 1 : 0);
    }
}