#include <iostream>
#include <fstream>
using namespace std;
// Высчитываем гипотинузу
int main()
{
	int iX1, iY1, iX2, iY2, iX, iY;
	ifstream inf("input.txt");
	ofstream outf("output.txt");
	inf >> iX1 >> iY1 >> iX2 >> iY2 >> iX >> iY;

	float fXmid = iX1 + (float)(iX2 - iX1) / 2; // X координата центра
	float fYmid = iY1 + (float)(iY2 - iY1) / 2; // Y координата центра

	float fXdiffDot = (float)fXmid - iX; // X разница в координатах
	float fYdiffDot = (float)fYmid - iY; // Y разница в координатах
	
	float fHypOfCentralSquare = (float)((fXmid - iX1) / 2) * ((fXmid - iX1) / 2) + ((fYmid - iY1) / 2) * ((fYmid - iY1) / 2); // Максимальное расстояние от центра до точки, когда точка принадлежит центру

	float fHyp = (float)fXdiffDot * fXdiffDot + fYdiffDot + fYdiffDot; // Длина гипотенузы

	outf << ((fHyp > fHypOfCentralSquare) ? "CORNER" : "CENTER");
	cout << ((fHyp > fHypOfCentralSquare) ? "CORNER" : "CENTER");
}