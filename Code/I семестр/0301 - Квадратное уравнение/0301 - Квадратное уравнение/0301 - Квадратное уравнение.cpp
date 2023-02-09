#include <iostream>
#include<cmath>
using namespace std;

float Resh(float a, float b, float c, int iState)
{
    float D = b * b - 4 * a * c;

    if (D >= 0)
    {
        switch (iState)
        {
            case 1:
            {
                float x = (-b + sqrtf(D)) / (2 * a);
                return x;
            }
            case 2:
            {
                float x = (-b - sqrtf(D)) / (2 * a);
                return x;
            }
        }
    }
    else
    {
        return NAN;
    }
}

int main()
{
    float a, b, c, x1, x2;
    cin >> a >> b >> c;

    x1 = Resh(a, b, c, 1);
    x2 = Resh(a, b, c, 2);
    if (not isnan(x1))
    {
        if (x1 != x2)
        {
            cout << x1 << " " << x2;
        }
        else
        {
            cout << x1;
        }
    }
}