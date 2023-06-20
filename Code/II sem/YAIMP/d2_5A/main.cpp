#include <iostream>
#include <cmath>
using namespace std;

const float leftB = -5;
const float rightB = 5;
const float epsilon = 0.001;
const float goldProportion = 1.618;

float f(float x)
{
    return pow(x, 3) + 3 * pow(x, 2) - 9 * x - 5 + 5 * sin(x) - 5 * cos(x);
}

float goldPropMethod(const bool& state, float a = leftB, float b = rightB)
{
    // state = false - min
    // state = true - max

    float x1 = b - ((b - a) / goldProportion);
    float x2 = a + ((b - a) / goldProportion);

    float y1 = f(x1), y2 = f(x2);

    if(state == (y1 >= y2))
    {
        a = x1;
    }
    else
    {
        b = x2;
    }

    if(fabs(b - a) <= epsilon)
    {
        return (a + b) / 2; // Если погрешность <= epsilon
    }
    return goldPropMethod(state, a, b);
}

int main()
{
    for(int i = 0; i <= 1; i ++)
    {
        cout << i + 1 << endl;
        float res = goldPropMethod(i);
        cout << "x = " << res << endl << "y = " << f(res) << endl << endl;
    }
}
