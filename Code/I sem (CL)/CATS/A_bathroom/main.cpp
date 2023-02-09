#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    ifstream inf ("input.txt");
    int length, height, side;
    inf >> length >> height >> side;

    int surfaceWall = length * height;
    int surfaceMozaico = side * side;

    ofstream outf ("output.txt");
    outf << ceil((float) surfaceWall / surfaceMozaico);
}
