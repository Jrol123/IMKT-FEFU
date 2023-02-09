#include <iostream>
#include <fstream>
using namespace std;

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

// Совпадают x или y у соседних пар
// Вертикальный или горизонтальный отрезок => Нет диагоналей
// Работать с разницами x и y
// Сравнение значений с одинаковыми соседями (20-40, 50-40)

int main()
{
    ifstream inf ("input.txt");

    int maxDiff = 0;

    int massX [50];
    int massY [50];


    int countTop;
    inf >> countTop;

    for (int index = 0; index < countTop; index ++)
    {
        int x, y;
        inf >> x >> y;

        for (int subIndex = 0; subIndex < index; subIndex++)
        {
            if ((x == massX[subIndex]) || (y == massY[subIndex]))
            {
                maxDiff = max(maxDiff, max(x - massX[subIndex], y - massY[subIndex]));
            }
        }
        massX[index] = x;
        massY[index] = y;
    }

//    for(int index = 0; index < countTop; index ++)
//    {
//        int x, y;
//        inf >> x >> y;
//
//        massExtrX[0] = min(massExtrX[0], x);
//        massExtrY[0] = min(massExtrY[0], y);
//
//        massExtrX[1] = max(massExtrX[1], x);
//        massExtrY[1] = max(massExtrY[1], y);
//    }
    inf.close();

    ofstream outf ("output.txt");
    outf << maxDiff;
    cout << maxDiff;
    outf.close();
}
