#include <iostream>
#include <cmath>
#include <fstream>
//#include <vector>
static const double coeficient = 1.247; // Коэффициент проверки
// Не знаю, почему 1.247
// https://habr.com/ru/post/204600/

using namespace std;

// Сортировка расчёской + структура.

struct Heights
{
    double height = -1;
    string massNames [10];
    int nextFreeSpot = 1;
};
// Не работало с вектором

int main()
{
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");
    int countOfSoldiers;
    inf >> countOfSoldiers;

    Heights massHeights [countOfSoldiers];
    int nextFreeSpot = 0;

    for (int index = 0; index < countOfSoldiers; index ++)
    {
        double height; string name; inf >> height >> name;

        int findIndex = 0;
        for (; findIndex < nextFreeSpot; findIndex++)
        {
            if (massHeights[findIndex].height == height)
            {
                break;
            }
        }
        if (findIndex == nextFreeSpot)
        {
            massHeights[nextFreeSpot].height = height;
            massHeights[nextFreeSpot].massNames[massHeights[nextFreeSpot].nextFreeSpot - 1] = name;
            nextFreeSpot ++;
        }
        else
        {
            massHeights[findIndex].massNames[massHeights[findIndex].nextFreeSpot] = name;
            massHeights[findIndex].nextFreeSpot ++;
        }


    } // Ввод массива

    // diffSort - расстояние между сравниваемыми элементами.
    // https://habr.com/ru/post/204600/

    // Изменения коэффициента бесполезны.

    for(int diffSort = round(nextFreeSpot / coeficient); diffSort > 0; diffSort = round(diffSort / coeficient))
    {
        for (int firstIndex = 0; firstIndex + diffSort < nextFreeSpot; firstIndex ++)
        {
            double firstH = massHeights[firstIndex].height, secondH = massHeights[firstIndex + diffSort].height;
            if (firstH < secondH)
            {
                swap(massHeights[firstIndex], massHeights[firstIndex + diffSort]);
            }
        }
        if (diffSort == 2)
        {
            diffSort = 1;
        }
        else if  (diffSort == 1)
            break;
    }

    for (int index = 0; index < nextFreeSpot; index++)
    {
        for (int subIndex = 0; subIndex < massHeights[index].nextFreeSpot; subIndex++)
        {
            outf << massHeights[index].massNames[subIndex] << endl;
        }
    }
}

/*
 * Прерывается на 12-м тесте.
 * 11-й тест проходит за 0.593
 */
