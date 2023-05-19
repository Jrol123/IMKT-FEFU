#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

static const int maxCountProblems = 20;

struct Team
{
    int massCountTries [maxCountProblems] {0};
    int teamNumber;
    int total_solved = 0;
    int total_time = 0;
};

struct Try
{
    int teamNumber,problemNumber, time;
    bool state;
    Try()
    {

    }
    Try(int teamNumber, int problemNumber, int time, bool state)
    {
        this->teamNumber = teamNumber;
        this->problemNumber = problemNumber;
        this -> time = time;
        this-> state = state;
    }

    bool operator<(const Try& other) const {
        return time < other.time;
    }
};

bool compTeams(const Team& left, const Team& right)
{
    return ((left.total_solved > right.total_solved) or
            (left.total_solved == right.total_solved and left.total_time < right.total_time) or
            (left.total_solved == right.total_solved and left.total_time == right.total_time and left.teamNumber < right.teamNumber));
    // Проблема до этого компаратора (?)
}

bool compTryTeam(const Try& left, const Try& right)
{
    return left.teamNumber < right.teamNumber;
}

bool compTryTime(const Try& left, const Try& right)
{

    return left.time <= right.time;
//    return left.time < right.time;
}

int main()
{
    std::ifstream inf ("input.txt");
    int countTeams, countTries;
    inf >> countTeams >> countTries;
//    Try massTime[maxCountProblems][countTries];
    std::vector<std::vector<Try>> massTime (maxCountProblems, std::vector<Try>(countTries));
//    Team massTeams[countTeams];
    std::vector<Team> massTeams(countTeams);
    for (int teamNumber = 0; teamNumber < countTeams; teamNumber++)
    {
        massTeams[teamNumber].teamNumber = teamNumber + 1;
    } // Проименовывание команд
    int nowIndex[maxCountProblems] {0}; // Массив количества субмитов

    // На вход подаются: C, N, c_i, p_i, t_i, status
    // C - количество команд. <= 1000
    // N - количество ВСЕХ попыток. <= 1000.
    // c_i - № команды <= C
    // p_i - № проблемы <= 20
    // t_i - время попытки <= 36000
    // status - статус попытки
    // Если было много неудачных попыток, но не было удачных, то неудачные не засчитываются
    // Количество проблем нам не известно

    int lastProblemNumber = 0; // Оптимизация
    for(int i = 0; i < countTries; i++)
    {
        int teamNumber, problemNumber, time; bool state;
        inf >> teamNumber >> problemNumber >> time >> state;
        problemNumber -= 1;
        teamNumber -= 1;

        massTime[problemNumber][nowIndex[problemNumber]] = Try(teamNumber, problemNumber, time, state);
        massTeams[teamNumber].massCountTries[problemNumber] ++;
        nowIndex[problemNumber] ++;
        lastProblemNumber = std::max(lastProblemNumber, problemNumber);
    }
    inf.close();

    for(int indexProblem = 0; indexProblem <= lastProblemNumber; indexProblem++)
    {
        std::sort(massTime[indexProblem].begin(),
                  massTime[indexProblem].begin() + nowIndex[indexProblem],
                  compTryTeam);// Сортировка по командам

        int beginIndex = 0;
        for(int indexTeam = 0; indexTeam < countTeams; indexTeam++)
        {
            std::sort(&massTime[indexProblem][beginIndex],
                      &massTime[indexProblem][beginIndex + massTeams[indexTeam].massCountTries[indexProblem]],
                      compTryTime); // Сортировка по времени внутри номера для команды

            int time = 0;
            for(int indexTry = 0; indexTry < massTeams[indexTeam].massCountTries[indexProblem]; indexTry++)
            {
                if (!massTime[indexProblem][beginIndex + indexTry].state)
                {
                    time += 20 * 60;
                }
                else
                {
                    massTeams[indexTeam].total_solved += 1;
                    massTeams[indexTeam].total_time += time +
                                                       massTime[indexProblem][beginIndex + indexTry].time;
                    break;
                }
            }

            beginIndex = massTeams[indexTeam].massCountTries[indexProblem];
        }
    }

    std::sort(massTeams.begin(), massTeams.begin() + countTeams, compTeams);

    std::ofstream outf ("output.txt");
//    cout << massTeams[0].teamNumber;
    for (int index = 0; index < countTeams; ++index)
    {
//        cout << massTeams[index].teamNumber << " " << massTeams[index].total_solved << " " << massTeams[index].total_time << endl;
        outf << massTeams[index].teamNumber;
        outf << " ";
    }
    outf.close();
}

// Проблема в логике вычисления
