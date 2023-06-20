#include <iostream>
#include <cmath>
using namespace std;

int main() {
    long long xa, ya, xb, yb, xc, yc;
    cin >> xa >> ya >> xb >> yb >> xc >> yc;

    // Стороны треугольников
    pair<long long, long long> ab = {xb - xa, yb - ya};
    pair<long long, long long> ac = {xc - xa, yc - ya};
    pair<long long, long long> bc = {xc - xb, yc - yb};

    // Углы между сторонами
    long long a_angle = ac.first * ab.first + ac.second * ab.second,
            b_angle = ab.first * bc.first + ab.second * bc.second,
            c_angle = ac.first * bc.first + ac.second * bc.second;

    pair<long long, long long> point;

    // Проверка на углы
    if (a_angle == 0) {
        point.first = ab.first + ac.first + xa;
        point.second = ab.second + ac.second + ya;
    }
    else if (b_angle == 0) {
        point.first = -ab.first + bc.first + xb;
        point.second = -ab.second + bc.second + yb;
    }
    else if (c_angle == 0) {
        point.first = -ac.first - bc.first + xc;
        point.second = -ac.second - bc.second + yc;
    }

    cout << point.first << " " << point.second;
}
