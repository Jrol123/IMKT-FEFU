#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/*
int *SplitInt(string str, char cSubBreaker)
{
    string s = "";
    int sMass [2];
    int iC = 0;
    for (auto x : str)
    {
        if (x == cSubBreaker)
        {
            sMass[iC] = stoi(s);
            s = "";
            iC += 1;
        }
        else {
            s = s + x;
        }
    }
    return sMass;
}
*/
int main()
{
    int iCount, iSum = 0;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iCount;
    cout << iCount << endl << endl;

    string sTimeNum;
    int iC = 0;
    char cBreaker = ' ';
    char cExBreaker = '/n';
    //getline пока не EndOfFile
    while (iC < iCount)
    {
        int iTimeNum = 0;
        inf >> iTimeNum;
        iSum += iTimeNum;
        iC += 1;
    }
    /*
    while (!inf.eof()) // проверить delimetr
    {
        while (getline(inf, sTimeNum, cBreaker))
        {
            if (sTimeNum[(sizeof(sTimeNum) / 2) + 1] = '/')
            {
                int* iLowMassNum = SplitInt(sTimeNum, cExBreaker);
                for (int i = 0; i < 2; i ++)
                {
                    int iNum = iLowMassNum[i];
                    iC += 1;
                    iSum += iNum;
                    cout << iSum << " " << iNum << " " << iC << endl;
                }
            }
            else
            {
                iC += 1;
                iSum += stoi(sTimeNum);
                cout << iSum << " " << sTimeNum << " " << iC << endl; // можно сделать проверку середины на / и сплитовать
            }
        } //пока есть элементы
    }// проблемы с переходом на новую строку. элемент с брэйкером строки записывается как x[\n]y и суммируется только x, полностью выкидывается y
    Оно не работает. Вообще.
    */
    outf << iSum;
    cout << iSum << endl;
}
