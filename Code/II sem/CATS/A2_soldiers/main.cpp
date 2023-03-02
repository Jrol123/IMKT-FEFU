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

    int countOfSoldiers;
    inf >> countOfSoldiers;
    soldiers_t massSoldiers [countOfSoldiers];
    int count = 0;
//    soldiers_t finalSoldiers [countOfSoldiers];
    for(int i = 0; i < countOfSoldiers; i++)
    {
        inf >> massSoldiers[i].height;
        inf >> massSoldiers[i].name;
    }
    inf.close();

    for(int index = 0; index < countOfSoldiers; index++)
    {
        float maxHeight = 0;
        int needIndex = -1;

        for(int i = index; i < countOfSoldiers; i++)
        {
            if (maxHeight < massSoldiers[i].height)
            {
                maxHeight = massSoldiers[i].height;
                needIndex = i;
            }
        }
        if (needIndex != -1)
        {
            for(int i = needIndex; i - index > 0; i--)
            {
                swap(massSoldiers[i], massSoldiers[i-1]);
                count ++;
            }
        }

//        finalSoldiers[index] = massSoldiers[needIndex];
        // bruteforce
        //Наверняка можно создать формулу
    }

    ofstream outf("output.txt");
    outf << count;
    outf.close();
}
