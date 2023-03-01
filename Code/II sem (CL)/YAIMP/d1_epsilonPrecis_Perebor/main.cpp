#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int prec = 4;
const float epsilon = pow(10, -prec);
const float a = -5;
const float b = 5;

double f(double x)
{
    return pow(x, 3) + 3 * pow(x, 2) - 9 * x - 5 + 5 * sin(x) - 5 * cos(x);
}

int main()
{
    cout << endl;
    float x, ad = a;
    float delta = 2 * epsilon;
    while (ad + delta <= b)
    {
         if (f(ad) * f(ad + delta) < 0)
         {
             cout << "interval = " << "[" << setprecision (prec) <<  ad << ", " << setprecision (prec) <<  ad + delta << "]" << endl;
             cout << "x = " << setprecision (prec) << ad + epsilon << endl << endl;
         }
         ad += delta;
    }
}
