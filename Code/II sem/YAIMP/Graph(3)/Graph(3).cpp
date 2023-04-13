#include "graphics.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <random>
#pragma comment(lib,"graphics.lib")
using namespace std;


int X0 = 400, Y0 = 450;
float scale = 55 / 2;
float lims[4] = { -5, 5, -5, 16 };  // Ограничения значений [xmin, xmax, ymin, ymax]

// Возвращает экранную x-координату из координаты на графике
int xcoord(float x) {
    return int(X0 + 2 * scale * x);
}

// Возвращает экранную y-координату из координаты на графике
int ycoord(float y) {
    return int(Y0 - scale * y);
}

// Линии осей
void axes(float dv) {
    line(0, Y0, X0 * 2 - 1, Y0);
    // line(X0, 0, X0, Y0 * 2 - 1);
    line(X0, 0, X0, 799);

    // Стрелки
    line(X0, 0, xcoord(dv / 2), scale * dv);
    line(X0, 0, xcoord(-dv / 2), scale * dv);
    line(X0 * 2 - 1, Y0, X0 * 2 - scale * dv, ycoord(dv / 2));
    line(X0 * 2 - 1, Y0, X0 * 2 - scale * dv, ycoord(-dv / 2));

    // Разметка осей
    char s[10];
    int least_intx = floor(lims[0]);
    int least_inty = floor(lims[2]);
    for (int i = least_intx; i <= lims[1]; i++) {
        line(xcoord(i), ycoord(-dv / 2), xcoord(i), ycoord(dv / 2));

        if (i != 0) {
            sprintf(s, "%d", i);
            outtextxy(xcoord(i) - 4, ycoord(-dv) + 3, s);
        }

        for (float j = i + dv; j < i + 1 && j < lims[1]; j += dv) {
            line(xcoord(j), ycoord(-dv / 4), xcoord(j), ycoord(dv / 4));
        }
    }

    for (int i = least_inty; i <= lims[3]; i++) {
        line(xcoord(-dv / 2), ycoord(i), xcoord(dv / 2), ycoord(i));

        if (i != 0) {
            sprintf(s, "%d", i);
            outtextxy(xcoord(dv) + 4, ycoord(i) - 5, s);
        }

        for (float j = i + dv; j < i + 1 && j < lims[3]; j += dv) {
            line(xcoord(-dv / 4), ycoord(j), xcoord(dv / 4), ycoord(j));
        }
    }
}

float f1(float x) {
    return  x * x * x + 2 * x * x - 8 * x + 1;
}

float f2(float x) {
    return -2 * sin(x) + 15 * cos(x);
}

// Рисование графиков функций
void plot(float func(float), float ds, int color = WHITE) {
    int xmin = lims[0],
        xmax = lims[1];

    float x, y, y2, h = (xmax - xmin) / ds;
    // cout << h;
    setcolor(color);
    for (x = xmin; x < xmax; x += h) {
        y = func(x);
        y2 = func(x + h);
        // cout << y << endl;
        if (lims[2] <= y && y <= lims[3] &&
            lims[2] <= y2 && y2 <= lims[3]) {
            line(xcoord(x), ycoord(y), xcoord(x + h), ycoord(y2));
        }
    }

    setcolor(WHITE);
}

// Нахождение точек пересечения
void intersection_points(vector<float>* inters_pts) {
    float c, a = -5, b = 5, eps = 0.001;
    while (a < b) {
        while (b - a > eps) {
            c = (a + b) / 2;

            if ((f1(a) - f2(a)) * (f1(c) - f2(c)) <= 0) {
                b = c;
            }
            else
                a = c;

            // cout << c << " ";
        }

        (*inters_pts).push_back((a + b - eps) / 2);
        // cout << "Solution: ";
        // cout << (a + b - eps) / 2 << endl;

        a = c + 2 * eps;
        b = 5;
        while ((f1(a) - f2(a)) * (f1(b) - f2(b)) > 0 && a < b) {
            a += 0.01;
            b -= 0.01;
            // cout << '(' << a << ' ' << b << ')' << endl;
        }
    }
}

// Вывод координат точки на график
void print_point(float x, float y, int dx, int dy) {
    char text[20];
    sprintf(text, "x=%.2f", x);
    outtextxy(xcoord(x) + dx, ycoord(y) + dy - 15, text);
    sprintf(text, "y=%.2f", y);
    outtextxy(xcoord(x) + dx, ycoord(y) + dy, text);
}

// Штриховка области, ограниченной двумя графиками функций
void hatch(float x1, float x2, float h) {
    float y1, y2;
    setcolor(DARKGRAY);
    for (float x = x1 + h; x < x2; x += h) {
        if (f1(x) > f2(x))
            y1 = f1(x), y2 = f2(x);
        else
            y1 = f2(x), y2 = f1(x);

        // if (y1 > lims[3])
        //     y1 = lims[3];

        y1 = y1 > lims[3] ? lims[3] : y1;

        // if (y2 < lims[2])
        //     y2 = lims[2];

        y2 = y2 < lims[2] ? lims[2] : y2;

        line(xcoord(x), ycoord(y1), xcoord(x), ycoord(y2));
    }

    setcolor(WHITE);
}

// Вычисление площади методом Монте Карло
float monte_carlo_method(float xmin, float xmax, int N) {
    float x, s = 0;
    for (int i = 0; i < N; i++) {
        x = xmin + (xmax - xmin) * ((float)rand() / RAND_MAX); // ОТ xmin до xmax
        s += f1(x) - f2(x);
    }

    return (xmax - xmin) * s / N;
}

// Вычисление площади методом трапеций
float trapezoids_method(float xmin, float xmax, float ds) {
    double s = 0;
    for (double x = xmin; x < xmax; x += ds) {
        s += (f1(x) - f2(x) + f1(x + ds) - f2(x + ds)) / 2;
    }

    s = abs(s * ds);

    return s;
}


int main() {
    // -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
    initwindow(X0 * 2, 600);

    // Оси
    axes(0.2);

    // Графики
    plot(f1, 4000, LIGHTRED);
    plot(f2, 4000, LIGHTGREEN);

    // Точки пересечения
    vector<float> intpts;
    intersection_points(&intpts);

    // Вывод точек пересечения
    char text[20];
    // Первая точка
    print_point(intpts[0], f1(intpts[0]), -70, 0);
    fillellipse(xcoord(intpts[0]), ycoord(f1(intpts[0])), 5, 5);

    /*
    // Вторая точка
    print_point(intpts[1], f1(intpts[1]), 15, 15);
    fillellipse(xcoord(intpts[1]), ycoord(f1(intpts[1])), 5, 5);
    */

    /*
    // Третья точка
    print_point(intpts[2], f1(intpts[2]), -70, 0);
    fillellipse(xcoord(intpts[2]), ycoord(f1(intpts[2])), 5, 5);
    */

    // Штриховка (двух) замкнутых областей
    hatch(intpts[0], intpts[1], 0.2);
    hatch(intpts[1], intpts[2], (intpts[2] - intpts[1]) / 11);

    // Вычисление площадей заштрихованных областей
    // for (int i = 100; i < 10000; i += 100)
    //     cout << monte_carlo_method(intpts[1], intpts[2], i) << " " << i << endl;

    float s11 = monte_carlo_method(intpts[0], intpts[1], 4100);
    float s12 = trapezoids_method(intpts[0], intpts[1], (intpts[1] - intpts[0]) / 1001);
    float s21 = abs(monte_carlo_method(intpts[1], intpts[2], 4900));
    float s22 = trapezoids_method(intpts[1], intpts[2], (intpts[2] - intpts[1]) / 1001);

    // Вывод значений площадей областей на график
    // char area_text[20];
    // Первая область
    sprintf(text, "S1=%.3f", s11);
    outtextxy(xcoord(-3.35), ycoord(7), text);
    sprintf(text, "S2=%.3f", s12);
    outtextxy(xcoord(-3.35), ycoord(7) + 15, text);

    // Вторая область
    sprintf(text, "S1=%.3f", s21);
    outtextxy(xcoord(2.65), ycoord(7), text);
    sprintf(text, "S2=%.3f", s22);
    outtextxy(xcoord(2.65), ycoord(7) + 15, text);

    getch();
    closegraph();

    return 0;
}