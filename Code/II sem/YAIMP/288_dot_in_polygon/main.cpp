#include <iostream>
using namespace std;

bool intersectionCheck(float mainDot[2], float x1, float y1, float x2, float y2)
{
    bool isHeight = (y2 < mainDot[1] && y1 >= mainDot[1])
            || (y1 < mainDot[1] && y2 >= mainDot[1]); // Если точка находится между 1-й и 2-й по высоте
    bool isLeft = x2 + (mainDot[1] - y2) / (y1 - y2) * (x1 - x2) <= mainDot[0]; // Если грань находится слева от точки
    // Выражение x0 через каноническое уравнение прямой
    // < mainDot[0] даёт 12 / 14. Последний тест проходит.
    // <= mainDot[0] даёт 13 / 14. Последний тест не проходит.

    // Возможно, дело в дробях
    return isHeight && isLeft;
}


int main()
{
    int countDots;
    float mainDot[2];
    cin >> countDots >> mainDot[0] >> mainDot[1];

    float massDots[countDots][2];
    for (int i = 0; i < countDots; i++)
    {
        cin >> massDots[i][0] >> massDots[i][1];
    }

    bool insidePolygon = false;
    int indexDot1 = countDots - 1; // Предыдущая точка
    for (int indexDot2 = 0; indexDot2 < countDots; indexDot2++)
    {
        if (intersectionCheck(mainDot,
                              massDots[indexDot1][0], massDots[indexDot1][1],
                              massDots[indexDot2][0], massDots[indexDot2][1]))
        {
            insidePolygon = !insidePolygon;// Чётное количество раз — переброс
            // Т. к. если прошёл чётное кол-во раз, то он находится за две грани от пустоты справа.
        }

        indexDot1 = indexDot2;
    }
    // float исправил лишь 1 тест

    if (insidePolygon)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
}