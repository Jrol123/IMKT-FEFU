#include <iostream>
#include <fstream>
using namespace std;

struct Team
{
    int total_solved = 0;
    int total_time = 0;
};

int main()
{
    ifstream inf ("input.txt");
    int countTeams, countTries;
    inf >> countTeams >> countTries;
    int massTime[20];

    for(int i = 0; i < countTries; i++)
    {
        int teamNumber, problemNumber, time; bool state;
        inf >> teamNumber >> problemNumber >> time >> state;
    }
}
