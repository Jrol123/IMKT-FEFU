#include <iostream>
using namespace std;

int main()
{
    const int iFullTrace = 109;
    int iSpeed, iTime;
    cin >> iSpeed >> iTime;

    int iBikeTrace = (((iSpeed * iTime) % (iFullTrace) + iFullTrace) % iFullTrace);

    cout << iBikeTrace;
}
