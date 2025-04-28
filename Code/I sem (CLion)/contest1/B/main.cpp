#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    string text; // Переполнения не будет
    string perexod;

    getline(inf, text);
    getline(inf, perexod);
    int N = stoi(perexod);


    string textFile[250000];

    for (int i = 0; i < N; i++)
    {
        getline(inf, textFile[i]);
        if ((text.find(textFile[i]) >= 0) && (text.find(textFile[i]) < 250001))
        {
            outf << 1;
        }
        else
        {
            outf << 0;
        }
        if (i + 1 < N)
        {
            outf << " ";
        }
    }

    inf.close();
    outf.close();
}