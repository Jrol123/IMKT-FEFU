//#include <iostream>
#include <fstream>
using namespace std;
const unsigned char lower = 'a';

int main()
{
    ifstream inf ("input.txt");

    char sym = inf.get();
    bool state = false;
    bool finState = true;

    while(sym != '\377')
    {
        if (sym < lower)
        {
            state = true;
        }
        if(state && sym >= lower)
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
