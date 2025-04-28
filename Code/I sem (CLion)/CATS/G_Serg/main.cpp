#include <cmath>
#include <iostream>
using namespace std;


int main() {
    int countOfElements, countOfOperations;

    FILE *f1 = fopen("input.txt", "r");
    fscanf(f1, "%d", &countOfElements);

    int treesz = int(pow(2, ceil(log2(countOfElements)))); // Довод до степени двойки
    int frtree[treesz * 2];
    // Чтение массива
    for (int i = treesz; i < treesz * 2; i++)
    {
        if (i < countOfElements + treesz)
        {
            fscanf(f1, "%d", &frtree[i]);
        }
        else
        {
            frtree[i] = -float('inf');
        }
    }
    // 0-я ячейка никогда не используется!!!
    // С treesz, до countOfElements

    // Построение дерева отрезков
    for (int i = treesz - 1; i > 0; i--)
    {
        frtree[i] = max(frtree[i * 2], frtree[i * 2 + 1]); // локальные максимумы + максимумы из максимумов
//        (frtree[i*2] > frtree[i*2 + 1] ? frtree[i*2] : frtree[i*2 + 1]);
    }

    // Вывод дерева отрезков
//    for (int i = 1; i < treesz*2; i++)
//    {
//        printf("%d ", frtree[i]);
//        if (log2(i + 1) == ceil(log2(i + 1)))
//            printf("\countOfElements");
//    }

    fscanf(f1, "%d", &countOfOperations);
    int leftMove = 0, rightMove = 0;
    int finalMass[countOfOperations], maxElement = frtree[treesz];

    char moveto; // = getc(f1);
    fscanf(f1, "%c", &moveto);
    // fscanf(f1, "%c");
    // getc(f1);
    for (int i = 0; i < countOfOperations; i++)
    {
        // moveto = getc(f1);
        fscanf(f1, "%c", &moveto);
        // cout << moveto << " " << endl;
        if (moveto == 'R')
        {
            rightMove++;
        }
        else
        {
            leftMove++;
        }
        int leftIndex = treesz + leftMove; // От (включительно)
        int rightIndex = treesz + rightMove; // До (включительно)


        // cout << endl << l << " " << r << " = ";


        while (leftIndex < rightIndex - 1)
        {
            // Если левая или правая граница нечётна или чётна соответственно,
            // то они "захватывают" не всю пару чисел, а лишь одно число из неё
            if (rightIndex % 2 == 0)
            {
                maxElement = max(maxElement, frtree[rightIndex]); // граница "правого частичного" участка
            } // Если захватывает лишь частично
            if (leftIndex % 2 == 1)
            {
                maxElement = max(maxElement, frtree[leftIndex]); // граница "левого частичного" участка
            } // Если захватывает лишь частично

            leftIndex = (leftIndex + 1) / 2; // Сдвижение к максимумам вверх
            rightIndex = (rightIndex - 1) / 2; // Сдвижение к максимумам вниз
        } // Сведение всего к одному из двух нижеизложенных варианта

        if (leftIndex == rightIndex)
        {
            maxElement = max(maxElement, frtree[rightIndex]); // Сравнение максимумов пар или же элементов одной пары
        } // Одна точка
        else if (leftIndex == rightIndex - 1)
        {
            maxElement = max(maxElement, max(frtree[leftIndex], frtree[rightIndex]));
        } // Две точки

        // cout << maxElement << endl;

        finalMass[i] = maxElement;
        maxElement = -1000000000;
        // cout << finalMass[i] << " ";
    }

    fclose(f1);

    // Вывод ответа
    FILE *f2 = fopen("output.txt", "w");
    fprintf(f2, "%d", finalMass[0]); // Для корректного вывода

    for (int i = 1; i < countOfOperations; i++)
    {
        fprintf(f2, " %d", finalMass[i]);
    }

    fclose(f2);

    return 0;
}
