#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int iCount;
    const int iLength = 2001;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iCount;
    cout << iCount << endl << endl;
    int iMass[iLength] = { 0 }; // Как сделать объявление по int??

    for (int i = 0; i < iCount; i++)
    {
        int iT = 0;
        inf >> iT;
        iT = (iT + iLength) % iLength;
        iMass[iT % iLength] += 1;
    }
    for (int i = -1000; i <= 1000; i++)
    {
        int t = (iLength + i) % iLength;
        int iTime = iMass[t];
        if (iTime >= 1)
        {
            outf << i << " " << iTime << endl;
            cout << i << " " << iTime << endl;
        }
    }
    cout << endl;
}
