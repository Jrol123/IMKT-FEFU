#include "graphics.h"
#include <cmath>
#pragma comment(lib,"graphics.lib")
int main()
{
    float x, y, z;
    initwindow(500, 500); // открыть окно для графики

    setbkcolor(1);                                      // делаем синий цвет фона, на котором...
    line(50, 0, 50, 480); line(50, 200, 640, 200);     // ...рисуем координатные оси
    moveto(50, 200);                            // и переходим в начало координат,...

    x = -5;

    do
    {
        y = x * sin(x);
        z = sin(x);
        //lineto(50 + x * 50, 100 + (100 - (y * 20)));     // ..откуда рисуем график
        lineto(50 + x * 50, 100 + (100 - (z * 20)));
        x = x + 0.02;
    } while (x <= 5);

    getch();                 // ожидание нажатия пользователем любой клавиши 
    closegraph();        // выход из графического режима
    return 0;
}