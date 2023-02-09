#include <iostream>
using namespace std;
//*x / i
int main()
{
    double n, x, dSum = 1;
    cin >> n >> x;

    double fStartX = x;

    for (int i = 2; i < n + 2; i++)
    {
        dSum += x;
        x *= fStartX;
        x /= i;
    }

    cout << dSum << endl;
}