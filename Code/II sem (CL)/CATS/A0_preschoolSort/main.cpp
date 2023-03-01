//#include <iostream>
#include <fstream>
using namespace std;
const short int minNum = int('a');

int main()
{
    ifstream inf ("input.txt");

    char sym = inf.get();
    bool state = false;
    bool finState = true;

    while(sym != '\377')
    {
        if (sym < minNum)
        {
            state = true;
        }
        if(state && sym >= minNum)
        {
            finState = false;
            break;
        }
        sym = inf.get();
    }
    inf.close();

    ofstream outf ("output.txt");

    if (finState)
    {
        outf << "YES";
    }
    else
    {
        outf <<"NO";
    }

    outf.close();
}
