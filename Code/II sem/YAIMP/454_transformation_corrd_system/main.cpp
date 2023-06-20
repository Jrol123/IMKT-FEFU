#include <iostream>
#include <iomanip>
using namespace std;

//В этой задаче мы находим координаты точки x1, y1 первой системы во второй системе
//и x2, y2 второй системы в первой системе

int main()
{
    double a, b, c, d, x1, x2, y1, y2;
    pair<double, double> vtorayasist, obr; // x | y
    cin >> a >> b >> c >> d >> x1 >> y1 >> x2 >> y2;

    // Базис
    vtorayasist.first = a; //нули второй системы (x)
    vtorayasist.second = b; //нули второй системы (y)

    obr.first = c - vtorayasist.first; //шаг второй системы x
    obr.second = d - vtorayasist.second; //шаг второй системы y

    //указываем точку, зная шаг второй системы (он не всегда = 1)
    pair<double, double> fPtr {(-a+x1)/obr.first, (-b+y1)/obr.second},
    sPtr {a+x2*obr.first, b+y2*obr.second}; // x | y

    cout << fixed << setprecision(3) << fPtr.first << " " << fPtr.second << " " << sPtr.first << " " << sPtr.second;

    return 0;
}