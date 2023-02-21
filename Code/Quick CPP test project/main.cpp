#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    char findSym, inputSym;
    inf >> findSym;
    inputSym = inf.get();
    int counter = 0;
    while (inputSym != '\377')
    {
        if (inputSym ==  findSym)
        {
            counter ++;
        }
        inputSym = inf.get();
    }
    inf.close();

    outf << counter;
    cout << counter;
    outf.close();
}