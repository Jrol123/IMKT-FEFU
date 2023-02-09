#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

int main1()
{
	int i;
	float x, e, s = 0;
	cin >> e;
	x = 1. / 26;
	i = 1;
	while (x > e)
	{
		s += x;
		x = 1. / (pow(4, i) + pow(5, i + 2));
		i++;
	}
	cout << s;
	return 0;
}
int main2()
{
	int iCount; // кол-во интервалов
	ifstream inf("input.txt");
	ofstream outf("output.txt");
	inf >> iCount;
	cout << iCount << endl << endl;

	float fA, fB, fRazn;
	inf >> fA >> fB;
	float fLeft = min(fA, fB);
	float fRight = max(fA, fB);
	fRazn = fRight - fLeft;

	cout << "F    " << fLeft << " " << fRight << endl;
	cout << "R    " << fRazn << endl << endl;
	int i = 0;

	while (fRazn >= 0 && i < iCount - 1)
	{

		float tA, tB;
		inf >> tA >> tB;
		float tLeft = min(tA, tB);
		float tRight = max(tA, tB);
		cout << "T    " << tLeft << " " << tRight << endl << endl;

		fLeft = max(tLeft, fLeft);
		fRight = min(tRight, fRight);
		fRazn = fRight - fLeft;

		cout << "F    " << fLeft << " " << fRight << endl;
		cout << "R    " << fRazn << endl << endl;

		i++;
	}
	if (fRazn >= 0)
	{
		outf << "Yes";
		cout << "Yes" << endl;
	}
	else
	{
		outf << "No";
		cout << "No" << endl;
	}
	return 0;
}

int main()
{
	int iState;
	cin >> iState;
	cout << endl;

	switch (iState)
	{
		case 1:
		{
			main1();
		}
		case 2:
		{
			main2();
		}
	}
}