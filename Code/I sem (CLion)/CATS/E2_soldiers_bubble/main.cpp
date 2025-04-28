//#include <iostream>
#include <fstream>
using namespace std;
// Пузырьковая сортировка
// Имена учитываются.
// Quick sort?

// Проблемы с выводом.

int main()
{
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");

    int countOfSoldiers; inf >> countOfSoldiers;

    double massHeights [countOfSoldiers];
    string massNames [countOfSoldiers];

    for (int index = 0; index < countOfSoldiers; index ++)
    {
        double height; string name; inf >> height >> name;

        massHeights[index] = height;
        massNames[index] = name;
    } // Ввод массива

    bool stateOfBubble = true;
    int indexStart = 0;
    int indexEnd = countOfSoldiers - 1;

    while (stateOfBubble)
    {
        stateOfBubble = false;

        for (int index = indexEnd; index > indexStart; index --)
        {
            if (massHeights[index] > massHeights[index - 1])
            {
                swap(massHeights[index], massHeights[index - 1]);
                swap(massNames[index], massNames[index - 1]);
                stateOfBubble = true;
            }
        }
        outf << massNames[indexStart] << endl; // Попытка убрать часть цикла вывода в основной код.
        indexStart ++;
    }
    outf << massNames[indexEnd];
}
