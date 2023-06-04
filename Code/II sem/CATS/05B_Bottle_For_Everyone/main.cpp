#include <queue>
#include <fstream>

int main()
{
    std::ifstream inf ("input.txt");
    unsigned int countPeople, countTotalSip;
    inf >> countPeople >> countTotalSip;

    std::priority_queue<long long> thirstMass;

//    unsigned int massPeople[countPeople];
    unsigned long long totalThirst = 0;
    for(int index = 0; index < countPeople; ++index)
    {
        int num = 0;
        inf >> num;
        thirstMass.push(num);
        totalThirst += num;
    }
    inf.close();

    for(unsigned int countSips = 0; (countSips < countTotalSip) & (totalThirst > 0); ++countSips)
    {
        long long thirstAmount = thirstMass.top();
        totalThirst -= thirstAmount - (thirstAmount / 10);
        thirstMass.pop();
        thirstMass.push(thirstAmount / 10);
    }

    std::ofstream outf ("output.txt");
    outf << totalThirst;
    outf.close();
    return 0;
}
