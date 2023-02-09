#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    float number; inf >> number;
    //cout << number << endl;
    int* l = (int*)&number;

    //cout << *l << endl;

    int pow = ((*l >> 23) & 255) - 127;
    // Получается всё вещественное число. Ищется порядок путём удаления мантиссы и отнимания ненужной 127 + срезания левой части

    if (number == 0)
    {
        pow = 0;
    }
    else if (pow < -126)
    {
        pow = -126; // Резерв для INF
    }


    outf << pow << endl;
    //cout << pow << endl;
}