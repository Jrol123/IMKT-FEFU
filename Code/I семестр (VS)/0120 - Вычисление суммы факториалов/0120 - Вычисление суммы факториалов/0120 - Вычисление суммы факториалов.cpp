#include <iostream>
using namespace std;

int main()
{
	float fLastNum, fThisNum = 1, fSum = 1;
	cin >> fLastNum;

	for (float fSchet = 1; fSchet < fLastNum+1; fSchet += 1)
	{
		fThisNum /= fSchet;
		fSum += fThisNum;
	}

	cout << fSum;
}

