#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const float leftBorder = -100;
const float rightBorder = 100;
const float discrStep = 0.001;

float func1(float x)
{
    return x * x;
}

float func2(float x)
{
    return 4 * cos(x);
}

float diffTrapezoidMethod(float(&f1)(float), float (&f2)(float), float begin = leftBorder, float end = rightBorder)
{
    float S = 0;
    for(float x = begin; x <= end; x += discrStep)
    {
        float y11 = f1(x), y21 = f2(x);
        float y12 = f1(x + discrStep), y22 = f2(x + discrStep);
        S += (y11 + y12 - y21 - y22) / 2;
    }

    return abs(S * discrStep); // h = discrStep (высота измеряется по-горизонтали)
}

void diffIntersectFinder(float(&f1)(float), float (&f2)(float), vector<float> (&massSol))
{
    for(float x = leftBorder; x < rightBorder; x += 2 * discrStep)
    {
        float t1 = f1(x) - f2(x);
        float t2 = f1(x + 2 * discrStep) - f2(x + 2 * discrStep);
        if (t1 * t2 <= 0)
        {
            cout << "Intersection point " << x + discrStep << endl;
            massSol.push_back(x + discrStep);
        }
    }
}

int main()
{
    vector<float> massSol;
    diffIntersectFinder(func1, func2, massSol);
    cout << endl;
    int count = massSol.size();
    for(int i = 0; i < count; i += 2)
    {
        float x1 = massSol[i], x2 = rightBorder;
        if (x1 > rightBorder || x1 < leftBorder)
        {
            continue;
        }
        if (i + 1 < count)
        {
            x2 = massSol[i + 1];
        }
        cout << "S" << i + 1 << " = " << diffTrapezoidMethod(func1, func2, x1, x2) << endl;
    }
}