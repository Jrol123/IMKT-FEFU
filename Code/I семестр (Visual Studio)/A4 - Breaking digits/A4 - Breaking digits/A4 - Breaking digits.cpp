#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int iNum;
    vector <int> iMass;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iNum;
    cout << iNum << endl << endl;

    const int iLength = (to_string(iNum)).size();

    for (int i = 0; i < iLength; i++)
    {
        iMass.push_back(iNum % 10);
        iNum /= 10;
    }

    for (int i = 0; i < iLength; i++)
    {
        for (int subI = 0; subI < iLength - 1 - i; subI++)
        {
            const int iI = subI + 1;
            int iLeft = iMass[subI];
            int iRight = iMass[iI];

            if (iLeft > iRight)
            {
                iMass[iI] = iLeft;
                iMass[subI] = iRight;
            }
        }
    }

    string sA = "";

    for (int i = iLength - 1; i > 0; i--)
    {
        outf << iMass[i];
        cout << iMass[i];
    }
    
    cout << endl << iMass[0] << endl;
    outf << endl << iMass[0];
}