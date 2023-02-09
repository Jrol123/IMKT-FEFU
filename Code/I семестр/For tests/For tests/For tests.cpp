#include <iostream>
using namespace std;

int main()
{
    int iCountOfX;
    cin >> iCountOfX;
    for (int i = 1; i <= iCountOfX; i++)
    {
        cout << (float)(i * i + i) / (i * i + i * 3 + 1) << endl;
    }
}