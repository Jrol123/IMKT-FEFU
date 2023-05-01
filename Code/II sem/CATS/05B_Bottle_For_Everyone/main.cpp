#include <iostream>
#include <algorithm>
#include <fstream>

/*
 * TL на 2-м тесте
 */

int main()
{
    std::ifstream inf ("input.txt");
    unsigned int countPeople, countTotalSip;
    inf >> countPeople >> countTotalSip;

    unsigned int massPeople[countPeople];
    unsigned int totalThirst = 0;
    for(int index = 0; index < countPeople; ++index)
    {
        inf >> massPeople[index];
        totalThirst += massPeople[index];
    }
    inf.close();

    sort(massPeople, massPeople + countPeople, std::greater<unsigned int>());

    for(unsigned int countSips = 0; (countSips < countTotalSip) & (totalThirst > 0); ++countSips)
    {
        totalThirst -= massPeople[0];
        massPeople[0] /= 10;
        totalThirst += massPeople[0];
        while (massPeople[0] > massPeople[1] && totalThirst > 0)
        {
            totalThirst -= massPeople[0];
            massPeople[0] /= 10;
            totalThirst += massPeople[0];
            countSips ++;
            if(countSips >= countTotalSip)
                break;
        }

        sort(massPeople, massPeople + countPeople, std::greater<unsigned int>());
    }

    std::ofstream outf ("output.txt");
    outf << totalThirst;
    outf.close();
    return 0;
}
