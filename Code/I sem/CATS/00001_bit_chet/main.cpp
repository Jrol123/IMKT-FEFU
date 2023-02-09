#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");

    setlocale(LC_ALL, "Russian");
    char symb = inf.get();
    int num = 0;
    int count = 0;

    for (int i = 1; i <= 64; i *= 2)
    {
        int state = symb % 2;
        num += state * i;
        count += state;
        symb = symb >> 1;
    }
    num += 128 * (count % 2);
    outf << char(num);
    cout << char(num);
    inf.close();
    outf.close();
}
