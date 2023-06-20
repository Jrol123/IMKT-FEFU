#include <iostream>
#include <cmath>
#include <string>
using namespace std;


int main()
{
    int n;
    cin >> n;

    float x[n], y[n];
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    // Векторы
    pair<float, float> ab = {x[n - 2] - x[n - 1], y[n - 2] - y[n - 1]},
                    bc = {x[n - 1] - x[0], y[n - 1] - y[0]};

    // Угол между двумя векторами
    float angle = ab.first * bc.second - ab.second * bc.first;
    bool sign = angle > 0;
    string ans = "YES";

    // Переход векторов по тройкам
    for (int i = 1; i < n; i++) {
        if (i == 1) {
            ab.first = x[n - 1] - x[0];
            ab.second = y[n - 1] - y[0];
            bc.first = x[0] - x[1];
            bc.second = y[0] - y[1];
        }
        else {
            ab.first = x[i - 2] - x[i - 1];
            ab.second = y[i - 2] - y[i - 1];
            bc.first = x[i - 1] - x[i];
            bc.second = y[i - 1] - y[i];
        }

        angle = ab.first * bc.second - ab.second * bc.first;
        if ((angle > 0 && !sign) || (angle < 0 && sign))
        {
            ans = "NO";
            break;
        }
    }

    cout << ans;
}
