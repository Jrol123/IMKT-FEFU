#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector <int> iMass;
    char cNum = getchar();

    while (cNum != '/n')
    {
        iMass.push_back(cNum);
        cNum = getchar();
    }
}