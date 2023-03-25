#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
const int countRazr = 26;

const char firstLetter = 65;

void radixSort(string mass[], int len, int bordRazr = 3)
{

    for(int i = 0; i < bordRazr; i++)
    {
        int razrMass [countRazr] {0};
        for(int j = 0; j < len; j++)
        {
            int razrNum = mass[j][3 - i - 1] - firstLetter;
            razrMass[razrNum] ++;
        } // Считывание i-го разряда у чисел
        // Сортировка подсчётом

        int count = 0;
        for(int j = 0; j < countRazr; j++)
        {
            int tmp = razrMass[j];
            razrMass[j] = count; // Отступ
            count += tmp;
        } // Определение первой позиции для числа

        string subMass [len];
        for (int j = 0; j < len; ++j)
        {
            int razrNum = mass[j][3 - i - 1] - firstLetter;
            subMass[razrMass[razrNum]] = mass[j];
            razrMass[razrNum] ++; // Следующая позиция для разряда
        }

        for(int j = 0; j < len; j++)
        {
            mass[j] = subMass[j];
        } // Перевод в основной массив

    } // Проход по всем разрядам
    // Счёт разрядов начинается с 0
}
int main()
{
    ifstream inf ("input.txt");
    int countFields;
    inf >> countFields;

    string mass [countFields];
    for (int i = 0; i < countFields; ++i)
    {
        inf >> mass[i];
    }
    inf.close();

    radixSort(mass, countFields);

    ofstream outf ("output.txt");

    for (int i = 0; i < countFields; ++i)
    {
        outf << mass[i] << endl;
    }
}
