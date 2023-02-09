#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int N;
    fin >> N;
    int a[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> a[i][j];
        }
    }

    int d = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i > 0)
                d = max(d, abs(a[i][j] - a[i - 1][j]));
            if (j > 0)
                d = max(d, abs(a[i][j] - a[i][j - 1]));
        }
    }

    fout << d;

    fin.close();
    fout.close();

    return 0;
}