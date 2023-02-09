#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");
    int massSym [255 + 1] {0};
    int massFirstLastIndex [2] {255, 1};//255 - ASCII 1 - length
    char sym = inf.get();
    while (sym != '\377')
    {
        int num = int(sym) + 1;
        massFirstLastIndex[0] = min(num, massFirstLastIndex[0]);
        massFirstLastIndex[1] = max(num, massFirstLastIndex[1]);
        massSym[num] += 1;
        massSym[0] += 1;
        sym = inf.get();
    }
    cout << setw(1) << "S" << setw(6) << "Code" << setw(8) << "Count" << " " << setw (10) << "Percent" << endl;
    for (int i = 0; i < (massFirstLastIndex[1] - massFirstLastIndex[0] + 1); i ++)
    {
        int maxIndex = 0;
        int maxCount = 0;
        for (int j = massFirstLastIndex[0]; j <= massFirstLastIndex[1]; j++)
        {
            if (maxCount < massSym[j])
            {
                maxIndex = j;
                maxCount = massSym[j];
            }
        }
        if (maxIndex != 0)
        {
            massSym[maxIndex] = 0;
            cout << setw(1) << char(maxIndex - 1) << setw(6) << maxIndex - 1 << setw(8) << maxCount << setw (10) << setprecision(3) << (float(maxCount) / massSym[0]) * 100 << "%" << endl;
        }

        // можно оптимизировать, добавив проверку на края
    }

}
