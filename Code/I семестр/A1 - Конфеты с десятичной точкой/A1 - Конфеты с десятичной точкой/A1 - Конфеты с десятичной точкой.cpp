#include <iostream>
#include <fstream>
using namespace std;

int NOD(int iNum1, int iNum2)
{
    int iMax = max(iNum1, iNum2);
    int iMin = min(iNum1, iNum2);
    do
    {
        iNum1 = iMax % iMin, iNum2 = iMin;
        iMax = iNum2;
        iMin = iNum1;
    } while (iMin > 0);
    cout << iMax << endl << endl;
    return iMax;
}

int main()
{
    int A, B, C, D;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> A >> B;
    cout << A << " " << B << endl << endl;


    int iNod = NOD(A, B);
    D = A / iNod;
    C = B / iNod;
    int iCount5 = 0, iCount2 = 0;
    while (C % 5 == 0)
    {
        C /= 5;
        iCount5 += 1;
    }
    while (C % 2 == 0)
    {
        C /= 2;
        iCount2 += 1;
    }
    int iCountMax = max(iCount2, iCount5);

    cout << C << " " << iCountMax << endl;
    outf << C << " " << iCountMax;
 
}