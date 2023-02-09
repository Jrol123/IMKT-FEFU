#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int NOD(int num1, int num2)
{
    int iMax = max(num1, num2);
    int iMin = min(num1, num2);
    do
    {
        num1 = iMax % iMin, num2 = iMin;
        iMax = num2;
        iMin = num1;
    } while (iMin > 0);

    return iMax;
}

int main()
{
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");

    int a, b; inf >> a >> b;

    int nod = NOD(a, b);
    int nok = (a * b) / nod;

    cout << setw(6) << nod << setw(6) << nok;
    outf << nod << " " << nok;
}
