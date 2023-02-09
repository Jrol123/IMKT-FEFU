#include <iostream>
#include <fstream>
using namespace std;


struct Light{
    int s;
    int hight;
};


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int N, L = 0;
    fin >> N;

    Light street [N];
    for (int i = 0; i < N; i++)
    {
        fin >> street[i].s >> street[i].hight;
    }

    // Инициализируем массив освещённости каждого метра улицы
    int lightness[100] = {};
    // for (int i = 0; i < N; i++)
    //     lightness[i] = 0;


    int start, end, s, h, ml = 0;
    for (int i = 0; i < N; i++)
    {
        s = street[i].s, h = street[i].hight;
        if (s - h < 0)
            start = 0;
        else
            start = s - h;

        if (s + h >= 100)
            end = 99;
        else
            end = s + h;

        // cout << start << " " << end << endl;
        for (int j = start; j < end; j++)
        {
            lightness[j]++;
            if (ml < lightness[j])
                ml = lightness[j];

            // cout << lightness[j] << " ";
        }

        // cout << endl;
    }

    fout << ml;

    fin.close();
    fout.close();

    return 0;
}
