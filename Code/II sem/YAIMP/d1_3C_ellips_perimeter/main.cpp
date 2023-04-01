#include <iostream>
#include <cmath>

using namespace std;

float ellipsis(float x, float a, float b)
{
    return sqrt(b * b - b * b / (a * a) * x * x);
}

float ramanudjanFormula(float a, float b)
{
    return M_PI * (3 * (a + b) - sqrt((3 * a + b) * (a + 3 * b)));
}

int main()
{
    float a = 2, b = 3;
    float x = 0, h = 0.05, len = 0;
    float y1, y2;
    while (x < a - h)
    {
        y2 = ellipsis(x + h, a, b);
        y1 = ellipsis(x, a, b);
        len += sqrtf(h * h + (y2 - y1) * (y2 - y1));
        x += h;
        // cout << "f(" << x << ") = " << y2 << endl;
    }

    cout << 4 * len << " ~ ";

    float L = ramanudjanFormula(a, b);
    cout << L << endl;
    cout << "Error: " << ((L - 4 * len) / L) * 100 << "%" << endl;
}
