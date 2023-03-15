#include "graphics.h"
#pragma comment(lib,"graphics.lib")
int main()
{
    initwindow(500, 500); // открыть окно для графики
    circle(200, 200, 100);
    getch();
    closegraph();

    return 0;
}