#include <iostream>
#include <vector>

std::vector<std::vector<int>> mulMatrix(const std::vector<std::vector<int>>&  matA,
                                        const std::vector<std::vector<int>>&  matB,
                                        const int& len)
{
    std::vector<std::vector<int>> c (len, std::vector<int>(len, 0));

    for(int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            for (int k = 0; k < len; k++)
            {
                c[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    return c;
}

void floidUorshell(std::vector<std::vector<int>>&  W,
                   const int& len)
{
    for (int k = 0; k < len; k++)
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                W[i][j] = W[i][j] || (W[i][k] && W[k][j]);
}

int main()
{
    int countDots;
    std::cin >> countDots;

    std::vector<std::vector<int>> matrix;

    for(int i = 0; i < countDots; i++)
    {
        matrix.push_back(std::vector<int>());
        for(int j = 0; j < countDots; j++)
        {
            bool state;
            std::cin >> state;
            matrix[i].push_back(state);
        }
    }
    std::cout << std::endl;

//    matrix = mulMatrix(matrix, matrix, countDots);

    floidUorshell(matrix, countDots);
    bool stat = true;
    for (int i = 1; i < countDots; i++)
    {
        if (matrix[0][i] == 0)
        {
            stat = false;
            break;
        }
    }
    switch (stat)
    {
        case true:
            std::cout << "YES";
            break;
        default:
            std::cout << "NO";
    }
//    for(int i = 0; i < countDots; i++)
//    {
//        for(int j = 0; j < countDots; j++)
//        {
//            std::cout << matrix[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
}
