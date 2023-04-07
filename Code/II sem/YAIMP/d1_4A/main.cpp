#include <iostream>
using namespace std;

const float leftBorder = 0;
const float rightBorder = 10;
const float discrStep = 0.01;

float parabola(float x)
{
    return x * x;
}

float trapezoidMethod(float x = leftBorder)
{
    float S = 0;
    for(; x < rightBorder; x += discrStep)
    {
        float y1 = parabola(x);
        float y2 = parabola(x + discrStep);
        S += (y1 + y2) / 2;
    }

    return abs(S * discrStep); // h = discrStep (высота измеряется по-горизонтали)
}

int main()
{
    cout << trapezoidMethod() << endl;
    // См. презентацию
}
