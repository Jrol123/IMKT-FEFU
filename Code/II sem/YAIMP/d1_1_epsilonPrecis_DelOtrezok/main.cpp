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

double df(double x)
{
    return 3 * pow(x, 2) + 6 * x - 9 + 5 * cos(x) + 5 * sin (x);
} // производная

int main()
{
    
}
