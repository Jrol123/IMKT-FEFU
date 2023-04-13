/*
13.
На трех железнодорожных станциях А1, А2 и А3 скопилось 120, 110 и 130 незагруженных вагонов.
Эти вагоны необходимо перегнать на железнодорожные станции В1, В2, В3, В4 и В5.
На каждой из этих станций потребность в вагонах соответственно равна 80, 60, 70, 100 и 50.
Тарифы перегонки одного вагона определяются матрицей:

2	4	1	6	7
3	3	5	4	2
8	9	6	3	4

Составьте такой план перегонок вагонов, чтобы общая стоимость была минимальной.
 */
#include <iostream>
using namespace std;

void solution(int costs[3][5], int ways[3][5],
              int matrixLoad [3], int matrixLim [5],
              int len, int nowIndex = 0, int index = 0)
{
    ways[index][nowIndex] += 1;
}

int main()
{
    int matrixCost [3][5] =
            {2, 4,	1,	6,	7,
            3,	3,	5,	4,	2,
            8,	9,	6,	3,	4};
    int matrixWay [3][5] {0};
    int loadA1 = 120, loadA2 = 110, loadA3 = 130;
    int limB1 = 80, limB2 = 60, limB3 = 70, limB4 = 100, limB5 = 50;
    int massLoad[3] = {loadA1, loadA2, loadA3};
    int massLim[5] = {limB1, limB2, limB3, limB4, limB5};
    int cost = INT_MAX;

    solution(matrixCost, matrixWay, massLoad, massLim, 15);
}
