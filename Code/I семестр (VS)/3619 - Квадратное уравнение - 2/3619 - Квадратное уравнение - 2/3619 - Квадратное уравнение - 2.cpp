#include <iostream>
#include <cmath>
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
    return NAN;
}

int main()
{
    float a, b, c;
    cin >> a >> b >> c;

    if (a == 0)
    {
        if (b == 0 && c == 0)
        {
            cout << 3;
        }
        else if (b != 0)
        {
            float fT = -(c / b);
            if (fT == -0)
            {
                cout << 1 << " " << 0;
            }
            cout << 1 << " " << fT;
        }
        else if (b == 0 && c != 0)
        {
            cout << 0;
        }
    }// упрощение памяти. Если a = 0, то x = -c/b. Если b = 0, то нет решений. Если всё равно 0, то бесконечно 
    else if (a != 0 && b == 0)
    {
        float fT = sqrt(-c) / sqrt(a);
        if (abs(fT) == 0)
        {
            cout << 1 << " " << fT;
        }
        else if (isnan(abs(fT)))
        {
            cout << 0;
        }// -1 0 0 -> NAN
        else
        {
            cout << 2 << " " << min(-fT, fT) << " " << max(-fT, fT);
        }
    }
    else
    {
        float x1 = Resh(a, b, c, 1), x2 = Resh(a, b, c, 2);
        if (not isnan(x1))
        {
            if (x1 == -0)
            {
                x1 = 0;
            }
            if (x2 == -0)
            {
                x2 = 0;
            }
            if (x1 != x2)
            {
                cout << 2 << " " << min(x1, x2) << " " << max(x1, x2);
            }
            else
            {
                cout << 1 << " " << x1;
            }
        }
        else
        {
            cout << 0;
        }
    }//Если имеет смысл высчитывать дискриминант
}