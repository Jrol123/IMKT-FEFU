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
        len += sqrt((f(x + discrStep) - f(x)) * (f(x + discrStep) - f(x)) + (discrStep * discrStep));
        x += discrStep;
    }

    cout << endl << len << endl;
}
