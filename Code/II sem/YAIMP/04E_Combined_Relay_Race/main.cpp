#include <iostream>
#include <fstream>

const unsigned short countDisciplines = 4;
const unsigned short countParticipants = 4;

void permutations(float (&line)[countParticipants][countDisciplines], int (&finalRes)[countParticipants], int (&res)[countParticipants],
                  unsigned short indexLastChar, float &minTime, float time = 0, unsigned short indexFirstChar = 0)
{
    if(indexFirstChar == indexLastChar)
    {
        if(minTime > time + line[3][3])
        {
            minTime = time;
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
            int j = index;
            for(int i = index - 1; i >= indexFirstChar; i--)
            {
                std::swap(line[i], line[j]);
                std::swap(res[i], res[j]);
                j --;
            } // Прокручивание всех цифр для лексикографического порядка
            permutations(line, finalRes, res, indexLastChar, minTime, time + line[indexFirstChar][indexFirstChar], indexFirstChar + 1);
            j = indexFirstChar;
            for(int i = indexFirstChar + 1; i<= index; i++)
            {
                std::swap(line[i], line[j]);
                std::swap(res[i], res[j]);
                j ++;
            } // Реверс прокручивание
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

    permutations(massTime, finalRes, res, countParticipants - 1, minTime);

    std::ofstream outf ("output.txt");
    for(int index : finalRes)
    {
        outf << index;
    }
    outf.close();

    return 0;
}
