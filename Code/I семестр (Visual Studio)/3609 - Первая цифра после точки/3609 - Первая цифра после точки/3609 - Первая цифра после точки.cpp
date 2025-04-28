#include <iostream>
using namespace std;

int main()
{
    double fNum;
    cin >> fNum;

    cout << (int)((fNum - int(fNum)) * 10);
}