#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream inf ("input.txt");

void massCreator(int len, vector<int> &mass)
{
    for (int i = 0; i < len; i++)
    {
        int num;
        inf >> num;
        mass[i] = num;
    }
}
// up - mass.size()
// bottom - 0
// nowPos - nowPos
bool binarySearch(int findNum, int bottomPos, int upperPos, vector<int>&mass)
{
    bool state = false;
    int nowPos = (upperPos + bottomPos)/2;
    int nowNum = mass[nowPos];
    if(upperPos < bottomPos)
    {
        return false;
    }
    else if (findNum == nowNum)
    {
        return true;
    }
    else
    {
        if (findNum > nowNum)
        {
            bottomPos = nowPos + 1;
        }
        else
        {
            upperPos = nowPos - 1;
        }
        return binarySearch(findNum, bottomPos, upperPos, mass);
    }
}

int main()
{
    ofstream outf ("output.txt");

    int countOfTriplets = 0;

    int len1, len2, len3;
    inf >> len1 >> len2 >> len3;

    vector<int> mass1 (len1);
    vector<int> mass2 (len2);
    vector<int> mass3 (len3);

    massCreator(len1, mass1);
    massCreator(len2, mass2);
    massCreator(len3, mass3);
    inf.close();
    // Можно ли запихать в цикл создание масивов?
    for (int i = 0; i < len1; i++)
    {
        int num = mass1[i];
        bool state = binarySearch(num, 0, len2 - 1, mass2);
        if (state)
        {
            bool state = binarySearch(num, 0, len3 - 1, mass3);
            if (state)
            {
                countOfTriplets ++;
            }
        }
    }
    outf << countOfTriplets;
    cout << countOfTriplets;
}
