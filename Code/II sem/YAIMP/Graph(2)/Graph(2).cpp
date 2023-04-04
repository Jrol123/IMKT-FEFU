#include "graphics.h"
#include <cmath>
#include <vector>
#pragma comment(lib,"graphics.lib")

using namespace std;

const float winX = 1920;
const float winY = 1200;

const float scale = (125 - 30) / 2;

const float limBX = -10;
const float limEX = 10;
const float limBY = -10;
const float limEY = 10;


int coord(float x, bool state)
{
    if (state == false)
    {
        return int(winY / 2 - scale * x);
    }
    return int(winX / 2 + 2 * scale * x);
}

void axes(float lengthBase)
{
    line(winX / 2, 0, winX / 2, winY); line(0, winY / 2, winX, winY / 2); // Оси

    // Стрелки
        //Y
    line(winX / 2, 0, coord(lengthBase / 2, true), scale * lengthBase);
    line(winX / 2, 0, coord(-lengthBase / 2, true), scale * lengthBase);
        //X
    int c = 13;
    line(winX - c, winY / 2, winX - scale * lengthBase - c, coord(lengthBase / 2, false));
    line(winX - c, winY / 2, winX - scale *  lengthBase - c, coord(-lengthBase / 2, false));

    //Разметка осей
    char symbols[10];
    for (int i = limBX; i <= limEX; i++)
    {
        line(coord(i, true), coord(-lengthBase / 2, false), coord(i, true), coord(lengthBase / 2, false));

        if (i != 0)
        {
            sprintf_s(symbols, "%d", i);
            outtextxy(coord(i, true) - 4, coord(-lengthBase, false) + 3, symbols);
        }

        for (float j = i + lengthBase; j < i + 1 && j < limEX; j += lengthBase)
        {
            line(coord(j, true), coord(-lengthBase / 4, false), coord(j, true), coord(lengthBase / 4, false));
        }
    }

    for (int i = limBY; i <= limEY; i++)
    {
        line(coord(-lengthBase / 2, true), coord(i, false), coord(lengthBase / 2, true), coord(i, false));

        if (i != 0)
        {
            sprintf_s(symbols, "%d", i);
            outtextxy(coord(lengthBase, true) + 4, coord(i, false) - 5, symbols);
        }

        for (float j = i + lengthBase; j < i + 1 && j < limEY; j += lengthBase)
        {
            line(coord(-lengthBase / 4, true), coord(j, false), coord(lengthBase / 4, true), coord(j, false));
        }
    }
}

// Нахождение точек пересечения
void intersection_points(vector<float> (&inters_pts), float f1(float), float f2(float), float eps)
{
    float c, a = -5, b = 5;
    while (a < b) {
        while (b - a > eps)
        {
            c = (a + b) / 2;

            if ((f1(a) - f2(a)) * (f1(c) - f2(c)) <= 0)
            {
                b = c;
            }
            else
                a = c;

            // cout << c << " ";
        }

        inters_pts.push_back((a + b - eps) / 2);
        // cout << "Solution: ";
        // cout << (a + b - eps) / 2 << endl;

        a = c + 2 * eps;
        b = 5;
        /*
        while ((f1(a) - f2(a)) * (f1(b) - f2(b)) > 0 && a < b) {
            a += 0.01;
            b -= 0.01;
            // cout << '(' << a << ' ' << b << ')' << endl;
        }
        */
    }
}

float f1(float x)
{
    return pow(x, 3) + 3 * pow(x, 2) - 9 * x - 5;
}

float f2(float x)
{
    return -5 * sin(x) + 5 * cos(x);
}

/*
float f3(float x)
{
    return sin(x) / x;
}

float f4(float x)
{
    return tan(x);
}

float f5(float x)
{
    return 5;
}
*/

void plot(float f(float), float discret, int color = WHITE)
{
    float x, y, y2, h = (limEX - limBX) / discret;
    // cout << h;
    setcolor(color);
    for (x = limBX; x < limEX; x += h)
    {
        y = f(x);
        y2 = f(x + h);
        // cout << y << endl;
        if (limBY <= y && y <= limEY &&
            limBY <= y2 && y2 <= limEY)
        {
            line(coord(x, true), coord(y, false), coord(x + h, true), coord(y2, false));
        }
    }
}

int main()
{
    float x, y, z;
    initwindow(winX, winY); // открыть окно для графики

    int const discr = pow(10, 4);

    // Рамки
    setcolor(LIGHTRED);
    line(coord(-5, true), coord(-5, false), coord(-5, true), coord(5, false));
    line(coord(5, true), coord(-5, false), coord(5, true), coord(5, false));
    line(coord(5, true), coord(-5, false), coord(-5, true), coord(-5, false));
    line(coord(5, true), coord(5, false), coord(-5, true), coord(5, false));
    setcolor(WHITE);

    // Оси
    axes(0.1);
    // Графики
    plot(f1, discr, LIGHTGREEN);
    plot(f2, discr, YELLOW);
    /*
    plot(f3, discr, LIGHTGREEN);
    plot(f4, discr, LIGHTBLUE);
    //plot(f5, discr, LIGHTRED);
    */
    // Точки пересечения
    vector<float> interPoints;
    intersection_points(interPoints, f1, f2, 0.01);

    setbkcolor(BLACK); // Фон

    getch();                 // ожидание нажатия пользователем любой клавиши 
    closegraph();        // выход из графического режима
    return 0;
}