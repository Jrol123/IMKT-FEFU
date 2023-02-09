#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream inf ("input.txt");
    int countOfTests; inf >> countOfTests;
    int massPointsForQuizes [countOfTests];

    for(int i = 0; i < countOfTests; i++)
    {
        int pointsForQuiz;
        inf >> pointsForQuiz;
        massPointsForQuizes[i] = pointsForQuiz;
    }

    int sumPoints = 0;

    for(int i = 0; i < countOfTests; i++)
    {
        char stateOfQuiz;
        inf >> stateOfQuiz;
        if (stateOfQuiz == 43)
        {
            sumPoints += massPointsForQuizes[i];
        }
    }
    inf.close();

    ofstream outf ("output.txt");
    outf << sumPoints;
}
