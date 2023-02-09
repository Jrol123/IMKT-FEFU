#include <iostream>
#include <fstream>
using namespace std;
//M < N
//M - максимальное число
//N - кол-во строк
int main() {
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");

    int N;
    inf >> N;// Де-факто не нужно.
    int M;
    inf >> M;
    char symb = inf.get();

    while (symb != -1)
    {
        symb = inf.get();
        int sum = 0;
        while (symb != '\n' && symb != -1)
        {
            sum += int(symb);
            symb = inf.get();
        }

        sum %= M;
        cout << sum << endl;
        outf << sum << endl;
    }
}
