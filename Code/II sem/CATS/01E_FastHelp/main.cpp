//#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void sortGreben (int mass[], int lenMass) // CLion берёт массив как ссылку
{
    for(int diffSort = round(lenMass / 1.247); diffSort > 0; diffSort = round(diffSort / 1.247))
    {
        //cout << diffSort << endl;
        for (int firstIndex = 0; firstIndex + diffSort < lenMass; firstIndex ++)
        {
            double firstH = mass[firstIndex], secondH = mass[firstIndex + diffSort];
            //cout << firstH << " " << secondH << endl;
            if (firstH > secondH)
            {
                swap(mass[firstIndex], mass[firstIndex + diffSort]);
                //cout << 1 << endl;
            }
//            else
//            {
//                cout << 0 << endl;
//            }
        }
        if (diffSort == 2)
        {
            diffSort = 1;
        }
        else if  (diffSort == 1)
            break;
//        initDiff /= 1.247;
//        initDiff = ceil(initDiff);
        //cout << endl;
    }
}

int main()
{
    ifstream inf ("input.txt");
    int countPlanes, timeUnload;
    inf >> countPlanes >> timeUnload;
    int massPlanes[countPlanes];
    for(int i = 0; i < countPlanes; i++)
    {
        inf >> massPlanes[i];
    }
    inf.close();
    sortGreben(massPlanes, countPlanes);

    int timeSum = timeUnload + massPlanes[0]; // Время разгрузки последнего + время полёта первого
    for(int i = 0; i < countPlanes - 1; i++)
    {
        timeSum += timeUnload;
        if (massPlanes[i + 1] - massPlanes[i] > timeUnload)
        {
            timeSum += massPlanes[i + 1] - massPlanes[i] - timeUnload;
        }
    }
    ofstream outf ("output.txt");
    outf << timeSum;
    outf.close();
}
