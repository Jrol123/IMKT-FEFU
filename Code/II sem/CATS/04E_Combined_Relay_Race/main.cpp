#include <iostream>
#include <fstream>
/*
 * Основная идея заключается в том, чтобы менять местами не участников, а дисциплины,
 * тем самым, вместо перебора участников, можно всегда брать элемент line[indexFirstChar][indexFirstChar] и не беспокоиться.
 */

const unsigned short countDisciplines = 4;
const unsigned short countParticipants = 4;

void transpose(float matrix[countParticipants][countDisciplines])
{
    float t;
    for(int i = 0; i < countParticipants; ++i)
    {
        for(int j = i; j < countDisciplines; ++j)
        {
            t = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = t;
        }
    }
}

void permutations(float (&line)[countParticipants][countDisciplines], int (&finalRes)[countParticipants], int (&res)[countParticipants],
                  unsigned short indexLastChar, float &minTime, float time = 0, unsigned short indexFirstChar = 0)
{
    if(indexFirstChar == indexLastChar)
    {
        if(time + line[3][3] < minTime)
        {
            minTime = time + line[3][3];
            for(int i = 0; i < countParticipants; i++)
            {
                finalRes[i] = res[i];
            }
        }
    }
    else
    {
        for (unsigned short index = indexFirstChar; index <= indexLastChar; index++)
        {
            if(index > indexFirstChar)
            {
                std::swap(line[indexFirstChar], line[index]);
                std::swap(res[indexFirstChar], res[index]);
            }

            permutations(line, finalRes, res, indexLastChar, minTime, time + line[indexFirstChar][indexFirstChar], indexFirstChar + 1);

            if(index > indexFirstChar)
            {
                std::swap(res[indexFirstChar], res[index]);
                std::swap(line[indexFirstChar], line[index]);
            }
        }
    }
}

int main()
{
    std::ifstream inf("input.txt");

    float massTime[countParticipants][countDisciplines];

    for (auto & indexPartic : massTime)
    {
        for(float & indexDisc : indexPartic)
        {
            inf >> indexDisc;
        }
    }
    inf.close();

//    permutations(massTime, ); // Теперь можно проходить по дисциплинам, а не по участникам.

    float minTime = 120 * 4; // См. ограничения задачи
    int finalRes[countParticipants]{1, 2, 3, 4};
    int res[countParticipants]{1, 2, 3, 4};

    transpose(massTime);
    permutations(massTime, finalRes, res, countParticipants - 1, minTime);

    std::ofstream outf ("output.txt");
    for(int index : finalRes)
    {
        outf << index << " ";
    }
    outf.close();

    return 0;
}
