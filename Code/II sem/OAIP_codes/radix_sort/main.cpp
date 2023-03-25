#include <iostream>
#include <cmath>
using namespace std;

const int countRazr = 10;

int razr(int num, int indexRazr)
{
    int step = pow(10, indexRazr);
    return num % (step * 10) / step;
}

void radixSort(int mass[], int len, int bordRazr = 5)
{
    unsigned int rankCheck = 0;

    for(int i = 0; i < bordRazr; i++)
    {
        int razrMass [countRazr] {0}; //0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        for(int j = 0; j < len; j++)
        {
            int razrNum = razr(mass[j], i);
            razrMass[razrNum] ++;
//            cout << razrNum << endl;
        } // Считывание i-го разряда у чисел
        // Сортировка подсчётом

        int count = 0;
        for(int j = 0; j < countRazr; j++)
        {
            int tmp = razrMass[j];
            razrMass[j] = count; // Отступ
            count += tmp;
        } // Определение первой позиции для числа

        int subMass [len];
        for (int j = 0; j < len; ++j)
        {
            int razrNum = razr(mass[j], i);
            subMass[razrMass[razrNum]] = mass[j];
            razrMass[razrNum] ++; // Следующая позиция для разряда
        }

        for(int j = 0; j < len; j++)
        {
            mass[j] = subMass[j];
        } // Перевод в основной масссив

    } // Проход по всем разрядам
    // Счёт разрядов начинается с 0

    // Для сортировки в обратную сторону потребуется поменять порядок
}

int main()
{
    int mass []{35, 64, 128, 11, 2, 34, 33, 999};

    radixSort(mass, 8, 3);

    cout << mass[2] << " " << mass[3] << " " << mass[4]; //33 34 35
}
