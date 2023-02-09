//#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

// Сортировка расчёской
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

    //3 - 1 = 2; 0 + 2 = 2
    // diffSort - расстояние между сравниваемыми элементами.
    // Не уверен, почему 1.247
    // https://habr.com/ru/post/204600/
    //double initDiff = ceil(countOfSoldiers / 1.247);
    for(int diffSort = round(countOfSoldiers / 1.247); diffSort > 0; diffSort = round(diffSort / 1.247))
    {
        //cout << diffSort << endl;
        for (int firstIndex = 0; firstIndex + diffSort < countOfSoldiers; firstIndex ++)
        {
            double firstH = massHeights[firstIndex], secondH = massHeights[firstIndex + diffSort];
            //cout << firstH << " " << secondH << endl;
            if (firstH < secondH)
            {
                swap(massHeights[firstIndex], massHeights[firstIndex + diffSort]);
                swap(massNames[firstIndex], massNames[firstIndex + diffSort]);
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
    for (int index = 0; index < countOfSoldiers; index ++)
    {
        outf << massNames[index] << endl;
        //cout << massNames[index] << endl;
    }
}