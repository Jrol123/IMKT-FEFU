#include <iostream>
using namespace std;

int main()
{
	int iCountOfNums; // число цифр в последовательности
	int iCountOfWrongNums = 0; // число вычёркиваемых цифр
	int iNum; // оперируемое число
	int iPrevNum; // предыдущее число
	bool bState; // статус последовательности в прошлом. false - опускается, true - поднимается
	bool bStateOfEqual = false; // статус последовательности в самом начале

	cin >> iCountOfNums;
	cin >> iPrevNum >> iNum;

	bState = (((iNum - iPrevNum) > 0) ? true : false);
	if (iNum == iPrevNum)
	{
		iCountOfWrongNums += 1;
		bStateOfEqual = true;
	}
	iPrevNum = iNum;


	for (int i = 2; i < iCountOfNums; i++)
	{
		cin >> iNum;
		bool bStateNow = (((iNum - iPrevNum) > 0) ? true : false); // статус последовательности в данный момент
		
		if ((bState == bStateNow && !bStateOfEqual) || iNum == iPrevNum)
		{
			iCountOfWrongNums += 1;
		}
		else
		{
			bState = bStateNow;
			bStateOfEqual = false;
		}

		iPrevNum = iNum;
	}
	cout << iCountOfWrongNums;
}