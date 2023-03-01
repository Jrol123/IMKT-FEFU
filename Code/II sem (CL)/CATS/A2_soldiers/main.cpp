#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct soldier
{
    float height;
    string name;
} soldiers_t;

// index-needIndex это кол-во операций, необходимое для перемещения элемента
// с index до needIndex
int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    int countOfSoldiers;
    inf >> countOfSoldiers;
    soldiers_t massSoldiers [countOfSoldiers];
    soldiers_t finalSoldiers [countOfSoldiers];
    for(int i = 0; i < countOfSoldiers; i++)
    {
        inf >> massSoldiers[i].height;
        inf >> massSoldiers[i].name;
    }

    for(int index = 0; index < countOfSoldiers; index++)
    {
        float maxHeight = 0;
        int needIndex;

        for(int i = index; i < countOfSoldiers; index++)
        {
            if (maxHeight < massSoldiers[i].height)
            {
                maxHeight = massSoldiers[i].height;
                needIndex = i;
            }
        }

        finalSoldiers[index] = massSoldiers[needIndex];
        // bruteforce
        //Наверняка можно создать формулу
    }
}
