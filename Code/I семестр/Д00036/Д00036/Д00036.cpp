#include <iostream>
using namespace std; // 3015
//summ * (n + 2);

int main()
{
    int iCount, iSum = 0;
    cin >> iCount;
    
    for (int i = 0; i < iCount + 1; i++)
    {
        iSum += i;
    }

    cout << iSum * (iCount + 2);
}