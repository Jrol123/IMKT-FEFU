//#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int compare(const void * x1, const void * x2)   // функция сравнения элементов массива
{
    return ( *(int*)x1 - *(int*)x2 );              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

// Неправильно сортирует при std::qsort
// Использование сразу двух куч?
int main()
{
    ifstream inf("input.txt");
    int count;
    inf >> count;
    vector<int> massNums(count);
//    int massNums[count];
    ofstream outf("output.txt");
    for(int index = 0; index < count; index ++)
    {
        inf >> massNums[index];
        qsort(&massNums[0], index + 1, sizeof(int), compare);
        // Каждый раз сортирует по-разному!!!
        outf << massNums[index / 2] << " ";
//        cout << massNums[index / 2] << " ";
    }
    inf.close();
    outf.close();
}
