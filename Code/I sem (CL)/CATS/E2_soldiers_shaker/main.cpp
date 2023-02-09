//#include <iostream>
#include <fstream>
using namespace std;
// Шэйкерная
// Имена учитываются.
// Quick sort?

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

    bool stateOfShaker = true;
    int indexStart = 0;
    int indexEnd = countOfSoldiers - 1;

    while (stateOfShaker)
    {
        stateOfShaker = false;

        for (int index = indexEnd; index > indexStart; index --)
        {
            if (massHeights[index] > massHeights[index - 1])
            {
                swap(massHeights[index], massHeights[index - 1]);
                swap(massNames[index], massNames[index - 1]);
                stateOfShaker = true;
            }
        }
        outf << massNames[indexStart] << endl; // Попытка убрать часть цикла вывода в основной код. Не получилось
        indexStart ++;

        if (! stateOfShaker)
            break;

        for(int index = indexStart; index < indexEnd; index ++)
        {
            if (massHeights[index] < massHeights[index + 1])
            {
                swap(massHeights[index], massHeights[index + 1]);
                swap(massNames[index], massNames[index + 1]);
                stateOfShaker = true;
            }
        }
        //outf << massNames[indexEnd] << endl;
        indexEnd --;
    }

    for (int index = indexStart; index < countOfSoldiers; index ++)
    {
        outf << massNames[index] << endl;
    }
}
