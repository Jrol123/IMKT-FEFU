#include <iostream>
#include <fstream>

static const int maxCountProblems = 20;
using namespace std;

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
};

void merge(Try arr[], int start, int end, int mid, int L, bool state)
{
    Try mergedArr[L];
    int leftIndex, rightIndex, counter;
    leftIndex = start;
    counter = start;
    rightIndex = mid + 1;

    while (leftIndex <= mid && rightIndex <= end)
    {
        int lA, bA;
        if (state)
        {
            lA = arr[leftIndex].teamNumber;
            bA = arr[rightIndex].teamNumber;
        }
        else
        {
            lA = arr[leftIndex].time;
            bA = arr[rightIndex].time;
        }
        if (lA <= bA)
        {
            // cout << arr[leftIndex] << " " << arr[rightIndex] << endl;
            mergedArr[counter] = arr[leftIndex];
            counter++;
            leftIndex++;
        } // Если берём из левой части
        else
        {
            mergedArr[counter] = arr[rightIndex];

            counter++;
            rightIndex++;
        } // Если берём из правой части
    }

    while (leftIndex <= mid)
    {
        mergedArr[counter] = arr[leftIndex];
        counter++;
        leftIndex++;
    }

    while (rightIndex <= end)
    {
        mergedArr[counter] = arr[rightIndex];
        counter++;
        rightIndex++;
    }

    for (leftIndex = start; leftIndex < counter; leftIndex++)
    {
        arr[leftIndex] = mergedArr[leftIndex];
    }
}

void mergeSort(Try arr[], int start, int end, int L, bool state)
{
    int mid;
    if (start < end)
    {
        mid = (start + end) / 2;
        mergeSort(arr, start, mid, L, state);
        mergeSort(arr, mid + 1, end, L, state);
        merge(arr, start, end, mid, L, state);
    }
}

void mergeTeams(Team arr[], int start, int end, int mid, int L)
{
    Team mergedArr[L];
    int leftIndex, rightIndex, counter;
    leftIndex = start;
    counter = start;
    rightIndex = mid + 1;

    while (leftIndex <= mid && rightIndex <= end)
    {
        if ((arr[leftIndex].total_solved > arr[rightIndex].total_solved) or
        (arr[leftIndex].total_solved == arr[rightIndex].total_solved and arr[leftIndex].total_time <= arr[rightIndex].total_time) or
        (arr[leftIndex].total_solved == arr[rightIndex].total_solved and arr[leftIndex].total_time == arr[rightIndex].total_time
        and arr[leftIndex].teamNumber > arr[rightIndex].teamNumber))
        {
            // cout << arr[leftIndex] << " " << arr[rightIndex] << endl;
            mergedArr[counter] = arr[leftIndex];
            counter++;
            leftIndex++;
        } // Если берём из левой части
        else
        {
            mergedArr[counter] = arr[rightIndex];

            counter++;
            rightIndex++;
        } // Если берём из правой части
    }

    while (leftIndex <= mid)
    {
        mergedArr[counter] = arr[leftIndex];
        counter++;
        leftIndex++;
    }

    while (rightIndex <= end)
    {
        mergedArr[counter] = arr[rightIndex];
        counter++;
        rightIndex++;
    }

    for (leftIndex = start; leftIndex < counter; leftIndex++)
    {
        arr[leftIndex] = mergedArr[leftIndex];
    }
} // Сортировка по командам

void mergeSortTeams(Team arr[], int start, int end, int L)
{
    int mid;
    if (start < end)
    {
        mid = (start + end) / 2;
        mergeSortTeams(arr, start, mid, L);
        mergeSortTeams(arr, mid + 1, end, L);
        mergeTeams(arr, start, end, mid, L);
    }
}

int main()
{
    ifstream inf ("input.txt");
    int countTeams, countTries;
    inf >> countTeams >> countTries;
    Try massTime[maxCountProblems][countTries]; // 20 * 1000 * 4 = 80 000 / 1024 = 79 kb
    Team massTeams[countTeams];
    for (int teamNumber = 0; teamNumber < countTeams; teamNumber++)
    {
        massTeams[teamNumber].teamNumber = teamNumber + 1;
    } // Проименовывание команд
    int nowIndex[maxCountProblems] {0};

    // На вход подаются: C, N, c_i, p_i, t_i, status
    // C - количество команд. <= 1000
    // N - количество ВСЕХ попыток. <= 1000.
    // c_i - № команды <= C
    // p_i - № проблемы <= 20
    // t_i - время попытки <= 36000
    // status - статус попытки
    // Если было много неудачных попыток, но не было удачных, то неудачные не засчитываются
    // Количество проблем нам не известно

    int lastProblemNumber = 0;
    for(int i = 0; i < countTries; i++)
    {
        int teamNumber, problemNumber, time; bool state;
        inf >> teamNumber >> problemNumber >> time >> state;
        problemNumber -= 1;
        teamNumber -= 1;
        massTime[problemNumber][nowIndex[problemNumber]] = Try(teamNumber, problemNumber, time, state);
        massTeams[teamNumber].massCountTries[problemNumber] ++;
        nowIndex[problemNumber] ++;
        lastProblemNumber = max(lastProblemNumber, problemNumber);
    }
    inf.close();

    for(int indexProblem = 0; indexProblem <= lastProblemNumber; indexProblem++)
    {
        mergeSort(massTime[indexProblem],
                  0,
                  nowIndex[indexProblem] - 1,
                  nowIndex[indexProblem],
                  true); // Сортировка по командам
        int beginIndex = 0;
        for(int indexTeam = 0; indexTeam < countTeams; indexTeam++)
        {
            mergeSort(massTime[indexProblem],
                      beginIndex,
                      beginIndex + massTeams[indexTeam].massCountTries[indexProblem] - 1,
                      massTeams[indexTeam].massCountTries[indexProblem],
                      false); // Сортировка по времени внутри номера -> команды

            int time = 0;
            for(int indexTry = 0; indexTry < massTeams[indexTeam].massCountTries[indexProblem]; indexTry++)
            {
                if (!massTime[indexProblem][indexTry + beginIndex].state)
                {
                    time += 20 * 60;
                }
                else
                {
                    massTeams[indexTeam].total_solved += 1;
                    massTeams[indexTeam].total_time += time +
                            massTime[indexProblem][indexTry + beginIndex].time;
                    break;
//                    if (!stateOfSolved)
//                    {
//                        massTeams[indexTeam].total_solved += 1;
//                        stateOfSolved = true;
//                    }
//                    massTeams[indexTeam].total_time += time +
//                                                       massTime[indexProblem][indexTry + beginIndex].time - prevBestTime;
//                    prevBestTime = massTime[indexProblem][indexTry + beginIndex].time;
                }
            }

            beginIndex = massTeams[indexTeam].massCountTries[indexProblem];
        } // Сортировка по времени
    }

    mergeSortTeams(massTeams, 0, countTeams - 1, countTeams);
    ofstream outf ("output.txt");
    outf << massTeams[0].teamNumber;
//    cout << massTeams[0].teamNumber;
    for (int index = 1; index < countTeams; ++index)
    {
//        cout << massTeams[index].teamNumber << " " << massTeams[index].total_solved << " " << massTeams[index].total_time << endl;
        outf << " ";
        outf << massTeams[index].teamNumber;
//        cout << " ";
//        cout << massTeams[index].teamNumber;
    }
    outf.close();
}
