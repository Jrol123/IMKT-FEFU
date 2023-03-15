#include <iostream>
#include <cmath>
using namespace std;

double f(double x)
{
    return pow(x, 3) + 3 * pow(x, 2) - 9 * x - 5 + 5 * sin(x) - 5 * cos(x);
}

void sol(float left_, float right_, float eps)
{

    float delta = 2 * eps, mid,
            left = left_,
            right = right_;
    bool cond = 0;

    if ((right - left) / 2 > delta)
    {

        while (right - left > delta)
        {

            mid = (right + left - eps / 5) / 2;

            if (f(right) * f(mid) <= 0)
            {
                left = mid, cond = 0;
            }
            else // > 0
            {
                // No sqrs
                right = mid, cond = 1;
            }
        }
        //cout << f(right) << " " << f(left) << " // " << right << " " << left << "\n";

        if (f(right) * f(left) <= 0) {
            cout << " [" << left << "; " << right + eps << "] -=> " << (left + right + eps) / 2 << "\n\n";

            if (!cond) sol(left + eps, 5, 0.001);
            else sol(-5, right - eps, 0.001);
        }
    }
}

int main()
{
    sol(-5, 5, 0.001);
}
