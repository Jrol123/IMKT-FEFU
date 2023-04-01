#include <iostream>
#include <cmath>

using namespace std;

const float S = 10, H = 2, g = 10, dstep = 0.1;
float a = 0;

float f(float x)
{
    float v0_arg = (S * S * g * cos(a)) / (S * sin(a) - H * cos(a)); // 2 * v0^2 * cos^2(x)
    return x * sin(a) / cos(a) - x * x * g / v0_arg - H;
}

void sol(float alf)
{
    a = M_PI * alf / 180; // Перевод в радианы
    float len = 0, x = 0;

    while (x <= S)
    {
        len += sqrt((f(x + dstep) - f(x)) * (f(x + dstep) - f(x)) + (dstep * dstep));
        x += dstep;
    }
    cout << len << endl;
}

int main()
{
    float alph1 = 35.5, alph2 = 65.8;
    sol(alph1);
    sol(alph2);
}
