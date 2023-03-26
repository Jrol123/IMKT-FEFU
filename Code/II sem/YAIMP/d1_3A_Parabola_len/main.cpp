#include <iostream>
#include <cmath>

using namespace std;

const unsigned short diapB = 0;
const unsigned short diapE= 10;
const float discrStep = 0.1;

float f(float x)
{
    return x * x;
}

int main()
{
    float len = 0, x = diapB;

    while(x <= diapE)
    {
        float diff = f(x + discrStep) - f(x);
        len += sqrt(diff * diff + discrStep * discrStep); // Метод Пифагора
        x += discrStep;
    }

    cout << endl << len << endl;
}
