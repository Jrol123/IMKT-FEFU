#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream inf ("input.txt");
    int leftSide, rightSide;
    inf >> leftSide >> rightSide;
    inf.close();

    ofstream outf ("output.txt");
//    (rstr2-rstr1)%4-(rstr1%2*2) == 1

    if ((max(leftSide, rightSide) - min(leftSide, rightSide)) % 4 - (min(leftSide, rightSide) % 2 * 2) == 1) // 3 - 2 == 1
    {
        outf << leftSide + rightSide - 1;
    }
    else
    {
        outf << 0;
    }
//    leftSide += rightSide - 1;
//    if(leftSide  % 2 == 0)
//    {
//        outf << leftSide;
//    }
//    else
//    {
//        outf << 0;
//    }
}
