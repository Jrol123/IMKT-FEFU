#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    int x1,x2,y1,y2,xp,yp;
//    bool prov = false;


    inf >> x1 >> y1 >> x2 >> y2;

    if((x1 > 0) && (x1 < 9) && (x2 > 0) && (x2 < 9) && (y1 > 0) && (y1 < 9) && (y2 > 0) && (y2 < 9)) // Проверка на выход за диапазон
    {
        bool stateOfDiagonal = (abs(x1 - x2) == abs(y1 - y2)); // Проверка на диагональ
        if(stateOfDiagonal && ((abs(x1 - x2) > 1) && (abs(y1 - y2) > 1))) // Разница в позициях > 1 (иначе всё плохо!)
        {
            if(((x1 < x2) && (y1 > y2)) || ((x1 > x2) && (y1 < y2)))
            {
                outf << ceil((x1 + x2) / 2) << " " << floor((y1 + y2) / 2);
            }
            else
            {
                outf << ceil((x1 + x2) / 2) << " " << ceil((y1 + y2) / 2);
            }
        }
        else if(stateOfDiagonal && (abs(x1 - x2) <= 1) && (abs(y1 - y2) <= 1))
        {
            outf << 0;
        }
        else if(!stateOfDiagonal) // Если не на одинаковых диагоналях
        {
            int flag = true;
            // В тупую проверяю на наличие позиции
            for(int i = 1; i <= 8; i++)
            {
                for(int j = 1; j <= 8; j++)
                {
                    xp = i;
                    yp = j;
                    stateOfDiagonal = ((abs(xp - x1)) == (abs(yp - y1))) && ((abs(xp - x2)) == (abs(yp - y2)));
                    if(stateOfDiagonal)
                    {
                        outf << xp << " " << yp;
                        flag = false;
                        break;
                    }
                }
                if(!flag)
                    break;
            }
            if(flag)
                outf << 0;
        }
    }
    else
        outf << 0;
}