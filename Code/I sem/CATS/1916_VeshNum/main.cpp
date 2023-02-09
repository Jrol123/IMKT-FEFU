#include <iostream>
using namespace std;

int main()
{
    int imConditionSettings[8][5] = {{2, 3, -1, -1, -1},
                                     {2, -1, 7, 4, 11},
                                     {2, -1, -1, -1, -1},
                                     {5, 6, -1, -1, -1},
                                     {5, -1, -1, -1, 11},
                                     {5, -1, -1, -1, -1},
                                     {8, -1, -1, -1, -1},
                                     {8, -1, -1, 4, 11}};

    int iSost = 1;
    int iNewCond;
    while(iSost != -1 && iSost != 10)
    {
        char cChar = cin.get();
        switch (cChar)
        {
            case '.':
            {
                iNewCond = 2;
                break;
            }
            case '+':
            {
                iNewCond = 1;
                break;
            }
            case '-':
            {
                iNewCond = 1;
                break;
            }
            default:
            {
                if (cChar == '\n')
                {
                    iNewCond = 4;
                    break;
                }
                else if (0 <= (int(cChar) - 48) && (int(cChar) - 48) <= 9)
                {
                    iNewCond = 0;
                    break;
                }
                else if (cChar == 'e' || cChar == 'E')
                {
                    iNewCond = 3;
                    break;
                }
                iSost = 1;
                iNewCond = 4;
                break;
            }
        }
        iSost = imConditionSettings[iSost - 1][iNewCond];
    }
    if (iSost == -1)
    {
        cout << "NO";
    }
    else
    {
        cout << "YES";
    }
    // в 20-м и 25-м NO
}
