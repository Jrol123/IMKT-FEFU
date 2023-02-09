#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int iCountOfColors;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iCountOfColors;
    for (int iDepth = 0; iDepth < iCountOfColors; iDepth++)
    {
        for (int iVert = 0; iVert < iCountOfColors; iVert++)
        {
            int iC = 0;
            for (int iHor = 0; iHor < iCountOfColors; iHor++)
            {
                iC += 1;
                string iT = to_string(1 + ((iDepth + iVert + iHor) % iCountOfColors));
                if (iC < iCountOfColors)
                {
                    iT = iT + " ";
                }
                outf << iT;
                cout << iT;
            }
            outf << endl;
            cout << endl;
        }
        cout << endl;
    }
}