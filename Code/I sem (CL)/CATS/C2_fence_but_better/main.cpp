#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int iCountOfPlanks; // Количество планок
    int iChetDiff = 0; // Отличие чётной последовательности от изначальной
    int iNeChetDiff = 0; // Отличие нечётной последовательности от изначальной
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iCountOfPlanks;
    cout << iCountOfPlanks << endl;

    int *iMassOfPlanks1 = (int*) calloc(iCountOfPlanks, sizeof(int)); // Нечётные
    int *iMassOfPlanks2 = (int*) calloc(iCountOfPlanks, sizeof(int)); // Чётныые

    for (int i = 0; i < iCountOfPlanks; i++)
    {
        int iPlank;
        inf >> iPlank;
        iMassOfPlanks1[i] = iPlank;
        iMassOfPlanks2[i] = iPlank;
    }
    if (iCountOfPlanks > 1)
    {
        if (iCountOfPlanks == 2)
        {
            int iPlank1 = iMassOfPlanks1[0], iPlank2 = iMassOfPlanks1[1];
            if (iPlank1 == iPlank2)
            {
                iPlank1 += 1;
            }
            outf << iPlank1 << " " << iPlank2;
            cout << iPlank1 << " " << iPlank2;
        }
        else
        {
            for (int i = 2; i < iCountOfPlanks; i++)
            {
                int iPlank3 = iMassOfPlanks1[i];

                int iPlank1_1 = iMassOfPlanks1[i - 2], iPlank1_2 = iMassOfPlanks1[i - 1];
                int iPlank2_1 = iMassOfPlanks2[i - 2], iPlank2_2 = iMassOfPlanks2[i - 1];
                if (((i + 1) % 2) != 0) // Если index 3-го элемента нечётный (1,2,3)
                {
                    if (iPlank1_1 <= iPlank1_2)
                    {
                        int iDiff = 1 + iPlank1_2 - iPlank1_1;
                        iMassOfPlanks1[i - 2] += iDiff;
                        iNeChetDiff += iDiff;
                    }
                    if (iPlank3 <= iPlank1_2)
                    {
                        int iDiff = 1 + iPlank1_2 - iPlank3;
                        iMassOfPlanks1[i] += iDiff;
                        iNeChetDiff += iDiff;
                    }

                    if (iPlank2_2 <= max(iPlank2_1, iPlank3))
                    {
                        int iDiff = 1 + max(iPlank2_1, iPlank3) - iPlank2_2;
                        iMassOfPlanks2[i - 1] += iDiff;
                        iChetDiff += iDiff;
                    }
                }
                else // Если index 3-го элемента чётный (2,3,4)
                {
                    if (iPlank1_2 <= max(iPlank1_1, iPlank3))
                    {
                        int iDiff = 1 + max(iPlank1_1, iPlank3) - iPlank1_2;
                        iMassOfPlanks1[i - 1] += iDiff;
                        iNeChetDiff += iDiff;
                    }

                    if (iPlank2_1 <= iPlank2_2)
                    {
                        int iDiff = 1 + iPlank2_2 - iPlank2_1;
                        iMassOfPlanks2[i - 2] += iDiff;
                        iChetDiff += iDiff;
                    }
                    if (iPlank3 <= iPlank2_2)
                    {
                        int iDiff = 1 + iPlank2_2 - iPlank3;
                        iMassOfPlanks2[i] += iDiff;
                        iChetDiff += iDiff;
                    }
                }
            }
            if (iNeChetDiff < iChetDiff)
            {
                for (int i = 0; i < iCountOfPlanks; i++)
                {
                    outf << iMassOfPlanks1[i] << " ";
                    cout << iMassOfPlanks1[i] << " ";
                }
            }
            else
            {
                for (int i = 0; i < iCountOfPlanks; i++)
                {
                    outf << iMassOfPlanks2[i] << " ";
                    cout << iMassOfPlanks2[i] << " ";
                }
            }
        }
    }
    else
    {
        int iPlank;
        inf >> iPlank;
        outf << iPlank;
    }
    cout << endl;
}