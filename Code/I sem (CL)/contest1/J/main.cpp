#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");

    string exitit;
    getline (inf, exitit);

    int countOfLists = stoi(exitit);

    string namesOfFishes [50] {""};
    int countOfFishes [50] {0};
    int indexOfNextPlace = 0;

    for (int indexList = 0; indexList < countOfLists; indexList ++)
    {
        getline(inf, exitit);
        int countOfFish = stoi(exitit);

        int FishesNowIter [50] {0};
        for (int indexFish = 0; indexFish < countOfFish; indexFish ++)
        {
            string nameFish;
            getline(inf, nameFish);
            int indexOfFish = 0;

            for(int i = 0; i < 50; i++)
            {
                if (namesOfFishes[i].empty())
                {
                    indexOfFish = -1;
                    break;
                }
                else if(namesOfFishes[i] == nameFish)
                {
                    indexOfFish = i;
                    break;
                }
            }

            if (indexOfFish != -1)
            {
                //FishesNowIter
                FishesNowIter[indexOfFish] += 1;
            }
            else
            {
                namesOfFishes[indexOfNextPlace] = nameFish;
                FishesNowIter[indexOfNextPlace] += 1;
                indexOfNextPlace ++;
            }
        }
        for(int i = 0; i < 50; i++)
        {
            if (namesOfFishes[i].empty())
            {
                break;
            }
            countOfFishes[i] = max(FishesNowIter[i], countOfFishes[i]);
        }
    }

    int minCount = 0;
    for (int i = 0; i < 50; i++)
    {
        if (namesOfFishes[i].empty())
        {
            break;
        }
        minCount += countOfFishes[i];
    }
    outf << minCount;
    cout << minCount;

}
