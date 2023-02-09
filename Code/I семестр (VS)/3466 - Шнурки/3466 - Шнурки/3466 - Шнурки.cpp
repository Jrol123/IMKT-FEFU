#include <iostream>
using namespace std;

int main()
{
    int iWidthBetween, iLengthBetween, iAddLen, iCountOfHoles;
    cin >> iWidthBetween >> iLengthBetween >> iAddLen >> iCountOfHoles;

    int iHor = (iCountOfHoles - 1) * 2 * iWidthBetween + iWidthBetween; // через все дырки проходит2 раза, кроме последней
    int iVert = iLengthBetween * (iCountOfHoles - 1) * 2; // кол-во расстояний между дырками * 2 * расстояние
    int iAdd = iAddLen * 2; // с двух сторон

    cout << iHor + iVert + iAdd;
}