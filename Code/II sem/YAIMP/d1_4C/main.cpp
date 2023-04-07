#include <iostream>
#include <cmath>

using namespace std;

const float leftBorder = -2;
const float rightBorder = 2;
const float discrStep = 0.09; // Меняется S При разных LB, RB

float precisEllips(float a, float b)
{
    return M_PI * a * b;
}

float ellips(float x, float a, float b)
{
    return b * (sqrt(a * a - x * x) / a);
} // От -2 —— до 2 по x
// От -3 —— до 3 по y

float trapezoidMethod(float a, float b)
{
    float S = 0;
    float y1 = ellips(leftBorder, a, b);
    for(float x = leftBorder; x <= rightBorder; x += discrStep)
    {
        float y2 = ellips(x + discrStep, a, b);
        if(!(isnan(y1) || isnan(y2)))
        {
            S += (y1 + y2) / 2;
        } // Проверка на нахождение в трапеции
        y1 = y2;
    } // Если сравнивать с кодом Сергея, то он считает лишь одну из четвертей, а потом размножает её на 4.
    // Но почему при этом у него точность выше?

    return abs(S * discrStep); // h = discrStep (высота измеряется по-горизонтали)
}

void pr4c()
{
    double a = 2, b = 3, S = 0, h = 0.09;
    for (double x = 0; x < a - h; x += h)
    {
        S += (ellips(x, a, b) + ellips(x + h, a, b)) / 2;
    }

    S *= h;
    cout << 4 * S << " ~ ";

    double S2 = M_PI * a * b;
    cout << S2 << endl;
    cout << "Error: " << ((S2 - 4 * S) / S2) * 100 << "%";
}

int main()
{
    float a = 2, b = 3;

    float methS = trapezoidMethod(a, b) * 2; // Умножение на 2, т. к. посчитана лишь "верхняя" половина
    // По-идее, можно домножать на 4, если знать, где центр и какая ширина.
    float precS = precisEllips(a, b);

    cout << methS << " ~ " << precS << endl << "Error: " << ((precS - methS) / precS) * 100 << "%";
    cout << endl << endl;
    pr4c();
}
