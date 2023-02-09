#include <iostream>
#include <fstream>
#include <vector>
#include "Д0003.h"
using namespace std;

int main()
{
	int iCountOfElem, iCountOfSubElem;
	ifstream inf("input.txt");
	//ifstream outf("output.txt");
	inf >> iCountOfElem;
	//cout << iCountOfElem << endl << endl;

	vector<int> iMass;
	int iSum = 0;

	for (int i = 0; i < iCountOfElem; i++)
	{
		int iNum = 0;
		inf >> iNum;
		iSum += iNum;
		iMass.push_back(iNum);
	}
	
	int deleter = iCountOfElem - 1;

	if (deleter > 0)
	{
		for (int i = 0; i < iCountOfElem; i++)
		{
			cout << (float)(iSum - iMass[i]) / deleter << "  ";
			//outf << (iSum - iNum) / (iCountOfElem - 1) << " ";
		}
	}
	else
	{
		cout << "NAN";
	}
	cout << endl;	
}