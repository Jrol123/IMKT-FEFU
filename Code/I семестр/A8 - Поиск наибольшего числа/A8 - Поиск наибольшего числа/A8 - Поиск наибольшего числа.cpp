#include <iostream>
#include <climits>
#
using namespace std;

int main()
{
	int iCount, iMax = numeric_limits<int>::min(), iNum;
	cin >> iCount;
	for (int i = 0; i < iCount; i++)
	{
		cin >> iNum;
		if (iNum > iMax)
		{
			iMax = iNum;
		}
	}
	cout << iMax;
}