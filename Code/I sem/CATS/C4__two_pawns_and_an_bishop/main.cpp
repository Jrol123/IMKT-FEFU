#include <iostream>
#include <fstream>
using namespace std;

/*
Всего 64 клетки.
Пешки должны или находиться на одной диагонали (отношение максимального x/y к минимальному x/y)
Или же между ними должно быть 6, 4, 2, 0 разница по x или y

 + Необходимо следить за тем, чтобы между пешками было расстояние (8,8 и 7,7 - 0)
 */

int main()
{
    ifstream inf ("input.txt");

    int bRow = 0;
    int bCol = 0;

    int massRows [2];
    int massCollumn [2];

    inf >> massRows[0] >>  massCollumn[0] >>  massRows[1]>> massCollumn[1];

    int maxX = max(massRows[0], massRows[1]);
    int minX = min(massRows[0], massRows[1]);

    int maxY = max(massCollumn[0], massCollumn[1]);
    int minY = min(massCollumn[0], massCollumn[1]);

    if (maxX - minX > 1 || maxY - minY > 1) // Ошибка как-то связана с этим условием
    {
        //float diffX = float(maxX) / minX;
        //float diffY = float(maxY) / minY;
        if (maxX - minX == maxY - minY)
        {
            bRow = maxX - 1;
            bCol = maxY - 1;
        } // На одной диагонали
        else if (maxX == minX)
        {
            if ((maxY - minY <= 8 - maxX) && (maxY - minY - 1) % 2 == 1)
            {
                bRow = (maxY - minY) / 2;
                bCol = bRow; // Неправильное вычисление Y
            }// Проверка на квадрат
            else
                cout << "Not a square" << endl;
        }
        else if (maxY == minY)
        {
            if ((maxX - minX <= 8 - maxY) && (maxX - minX - 1) % 2 == 1)
            {
                bCol = (maxX - minX) / 2;
                bRow = bCol;
            }// Проверка на квадрат
            else
                cout << "Not a square" << endl;
        }
    }

    ofstream outf ("output.txt");
    if (bRow == 0)
    {
        cout << 0;
        outf << 0;
    }
    else
    {
        cout << bRow << " " << bCol;
        outf << bRow << " " << bCol;
    }
}
