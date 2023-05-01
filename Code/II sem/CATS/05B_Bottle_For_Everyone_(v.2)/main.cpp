#include <queue>
#include <fstream>
//#include <iostream>

int main()
{
    std::ifstream inf ("input.txt");
    unsigned int countPeople, countTotalSip;
    inf >> countPeople >> countTotalSip;

    std::priority_queue<int> thirstMass;

//    unsigned int massPeople[countPeople];
    unsigned int totalThirst = 0;
    for(int index = 0; index < countPeople; ++index)
    {
        int num = 0;
        inf >> num;
        thirstMass.push(num);
        totalThirst += num;
    }
    inf.close();
    /*
     * Немного по-странному вставляет
     * См. тест 2
     */

    for(unsigned int countSips = 0; (countSips < countTotalSip) & (totalThirst > 0); ++countSips)
    {
        int thirstAmount = thirstMass.top();
        totalThirst -= thirstAmount - (thirstAmount / 10);
        thirstMass.pop();
        thirstMass.push(thirstAmount / 10);
    }

    std::ofstream outf ("output.txt");
    outf << totalThirst;
    outf.close();
    return 0;
}
