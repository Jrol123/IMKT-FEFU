#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;


int main() {
    int x1, y1, x2, y2, x, y;
    ifstream fin("input.txt");
    fin >> x1 >> y1 >> x2 >> y2 >> x >> y;
    fin.close();

    string place = "CENTER";
    int x0 = abs(x2 - x1), y0 = abs(y2 - y1);
    float x_center = x0 / 2., y_center = y0 / 2.;
    if (x2 < x1)
        x = abs(x - x2);
    else
        x = abs(x - x1);

    if (y2 < y1)
        y = abs(y - y2);
    else
        y = abs(y - y1);


    // Вычисляем расстояние до центра по теореме Пифагора,
    // принимая за стороны модули разности координат точки и координат центра
    // double to_center = sqrt(pow(abs(x - x_center), 2) + pow(abs(y - y_center), 2));

    // Если точка лежит внутри диагонали четверти,
    // обращённой к центру, то она ближе к центру
    bool to_center = false;

    // Расстояние до угла вычисляется через теорему Пифагора в случаях,
    // если координаты точки расположены в одной из 4-х четвертей относительно центра.

    // Если Точка лежит по другую сторону диагонали четверти,
    // обращённой к углу, то она ближе к углу
    bool to_corner = false;

    if (x > x_center && y > y_center && x_center != 0)
    {
        // cout << ((y - y_center) <= -(y_center / x_center) * x + y0) << " 1" << endl;
        if (float(y - y_center) <= -float(y_center / x_center) * x + y0)
            to_center = true;
        else
            to_corner = true;
    }
    else if (x < x_center && y > y_center && x_center != 0)
    {
        // cout << (y <= (y_center / x_center) * x + y_center) << " 2" << endl;
        if (y <= float(y_center / x_center) * x + y_center)
            to_center = true;
        else
            to_corner = true;
    }
    else if (x < x_center && y < y_center && x_center != 0)
    {
        // cout << (y >= -(y_center / x_center) * x + y_center) << " 3" << endl;
        if (y >= -float(y_center / x_center) * x + y_center)
            to_center = true;
        else
            to_corner = true;
    }
    else if (x > x_center && y < y_center && x_center != 0)
    {
        // cout << (y <= (y_center / x_center) * x) << " 4" << endl;
        if (y >= float(y_center / x_center) * x - y_center)
            to_center = true;
        else
            to_corner = true;
    }

    if (x1 == y1 && y1 == 0 && (x2 == 0 ^ y2 == 0))
    {
        if (x2 == 0)
        {
            cout << "!!";
            to_center = abs(y_center - y) <= y_center / 2;
            to_corner = ~to_center;
        }
        else
        {
            cout << " y2 = 0";
            to_center = abs(x_center - x) <= x_center / 2;
            to_corner = ~to_center;
        }
    }
    else if (x2 == y2 && y2 == 0 && (x1 == 0 ^ y1 == 0))
    {
        if (x1 == 0)
        {
            to_center = abs(y_center - y) <= y_center / 2;
            to_corner = ~to_center;
        }
        else
        {
            to_center = abs(x_center - x) <= x_center / 2;
            to_corner = ~to_center;
        }
    }
    else
    {
        if (x == x_center && y == y_center)
            place = "CENTER";
        else if ((x == 0 || x == x0) && (y == 0 || y == y0))
            place = "CORNER";
        else if ((x == x_center && (y == 0 || y == y0)))
        {
            if (y_center <= x_center)
                place = "CENTER";
            else
                place = "CORNER";
        }
        else if (y == y_center && (x == 0 || x == x0))
        {
            if (x_center <= y_center)
                place = "CENTER";
            else
                place = "CORNER";
        }
    }

    if (to_center)
        place = "CENTER";
    else if (to_corner)
        place = "CORNER";

    ofstream fout;
    fout.open("output.txt");

    fout << place;
    fout.close();

    return 0;
}