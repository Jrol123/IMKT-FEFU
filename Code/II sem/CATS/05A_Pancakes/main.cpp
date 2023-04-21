#include <iostream>
#include <fstream>
using namespace std;

const unsigned char burned = 'B';

int main()
{
    ifstream inf("input.txt");

    int countPancakes;
    inf >> countPancakes;

    char statPancake;
    inf >> statPancake;
    int countOfSwaps = 0;
    bool statOfSequence = (statPancake != burned); // 1 => Whites, 0 => Blacks

    if (!statOfSequence)
    {
        countOfSwaps += 1;
    }
    for(int index = 1; index < countPancakes; index++)
    {
        inf >> statPancake;
        if ((statPancake == burned) & statOfSequence)
        {
            countOfSwaps += 2;
            statOfSequence = false;
        }
        else if ((statPancake != burned) & !statOfSequence)
        {
//            countOfSwaps += 2;
            statOfSequence = true;
        }
    }
    inf.close();

    ofstream outf("output.txt");
    outf << countOfSwaps;
    outf.close();
}
