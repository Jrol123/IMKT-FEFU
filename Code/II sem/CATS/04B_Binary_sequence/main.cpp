#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string Razr(int iCountofPeriod, string sNum)
{
    if (iCountofPeriod > 0)
    {
        for (int i = 0; i < 2; i++)
        {
            Razr(iCountofPeriod - 1, sNum + to_string(i));
        }
    }
    else
    {
        ofstream outf("output.txt", ios::app);
        outf << sNum << endl;
        cout << sNum << endl;
    }
    return "0";
}

int main()
{
    int iCountOfPeriod; // количество разрядов
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    inf >> iCountOfPeriod;
    cout << iCountOfPeriod << endl << endl;

    string sNum = "";
    Razr(iCountOfPeriod, sNum);
    cout << endl;
}