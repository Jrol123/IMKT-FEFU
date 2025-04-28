#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int iNum, iCount = 0;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iNum;
    cout << iNum << endl << endl;

    for (int iSubNum = iNum; iSubNum > ((iNum / 2)); iSubNum--)
    {
        bool state = true;
        string sSubNum = to_string(iSubNum);
        string sTime(sSubNum.rbegin(), sSubNum.rend()); // не реверсировалось с помощью reverse (begin(), end())
        int iRevSubNum = stoi(sTime);
        if (trunc(log10(iRevSubNum)) + 1 < trunc(log10(iSubNum)) + 1)
        {
            state = false;
        }
        if (iSubNum + iRevSubNum == iNum)
        {
            iCount += 1;
            if (state)
            {
                iCount += 1;
            }
        }
    }
    string sSubNum = to_string(iNum/2);
    string sTime(sSubNum.rbegin(), sSubNum.rend()); // не реверсировалось с помощью reverse (begin(), end())
    int iRevSubNum = stoi(sTime);
    if ((iNum / 2) + iRevSubNum == iNum)
    {
        iCount += 1;
    }
    cout << iCount << endl;
    outf << iCount;
}