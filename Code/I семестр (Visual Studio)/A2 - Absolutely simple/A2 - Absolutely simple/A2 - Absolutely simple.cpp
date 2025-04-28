#include <fstream>
#include <iostream>
using namespace std;
//abs(Num - 100)
int main() {
    int iNum, iRemNum, iEndCount;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iNum;
    cout << "Input num: " << iNum << endl << endl;

    iRemNum = abs(iNum % 100);
    iEndCount = abs(iNum / 100);

    iEndCount += 1; // убирание лишней проверки на 50 и 0 (50 -> 50; 100 -> 0 -> 100)

    if (iNum < 0)
    {
        iEndCount += 2;
    } // -1 -> 101 -> 1 (+ 2 операции)

    iNum = abs(iNum); // для следующего условия

    if (((iNum < 100) && (iNum >= 0) && (iNum != 50)) || ((iRemNum != 50) && (iRemNum != 0)))
    {
        iEndCount += 1;
    }// Если изначальное число < 100 но >= 0 и != 50 т. к. изначальная прибавка +1 || Если изначальное число >= 100 Но остаток от деления != 50 или 100

    cout << "End count: " << iEndCount << endl;
    outf << iEndCount;
}