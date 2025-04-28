#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double P, X, K; int Y; // P - проценты, X - Рубли, Y - копейки, K - кол-во лет
	cin >> P >> X >> Y >> K;

	P = 1 + (P / 100);

	for (int i = 0; i < K; i++)
	{
		double t = 0;
		X *= P;
		double dTime = modf(X, &t);
		if (dTime != 0)
		{
			Y = Y * P + dTime * 100;
		}
		else
		{
			Y *=  P;
		}
		X = trunc(X);
	}

	X += Y / 100;

	cout << int(X) << " " << Y % 100;
}