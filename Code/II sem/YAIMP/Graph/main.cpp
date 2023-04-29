#include <iostream>
#include <fstream>
#include <vector>

static const unsigned int maxCountVert = 26;
static const unsigned char firstChar = 'A';

int main()
{
    std::ifstream inf("input.txt");

    std::string line; // Ребро
    std::vector<std::string> vectorLines;
    unsigned char lastSymbol = firstChar; // Значение последней вершины

    while(std::getline(inf, line))
    {
        lastSymbol = (line[0] > lastSymbol) ? line[0] : lastSymbol;
        lastSymbol = (line[1] > lastSymbol) ? line[1] : lastSymbol;
        vectorLines.push_back(line);
    }
    inf.close();

    for(auto& line: vectorLines)
    {
        std:: cout << line << std::endl;
    } // Вывод списка рёбер
    std::cout << std::endl << std::endl << std::endl;

    bool matrix_adj [maxCountVert][maxCountVert]{}; // По-умолчанию все false
    for (auto& line : vectorLines)
    {
        matrix_adj[line[0] - firstChar][line[1] - firstChar] = true;
        matrix_adj[line[1] - firstChar][line[0] - firstChar] = true;
    } // Матрица смежности
    for (int i = 0; i < lastSymbol - firstChar + 1; i++)
    {
        for (int j = 0; j < lastSymbol - firstChar + 1; j++)
        {
            std::cout << matrix_adj[i][j] << " ";
        }
        std::cout << std::endl;
    } // Вывод матрицы смежности
    std::cout << std::endl << std::endl << std::endl;



    std::vector<std::vector<int>> matrix_int(maxCountVert, std::vector<int>(vectorLines.size(), 0));
//    int matrix_inc[maxCountVert][vectorLines.size()]{0};
    for (int index = 0; index < vectorLines.size(); index++)
    {
        line = vectorLines[index];
        matrix_int[line[0] - firstChar][index] = 1;
        if(line[0] != line[1])
        {
            matrix_int[line[1] - firstChar][index] = 1;
        }
    } // Матрица инцидентности

    for (int i = 0; i < lastSymbol - firstChar + 1; i++)
    {
        for (int j = 0; j < vectorLines.size(); j++)
        {
            std::cout << matrix_int[i][j] << " ";
        }
        std::cout << std::endl;
    } // Вывод матрицы инцидентности
    std::cout << std::endl << std::endl << std::endl;






    std::ofstream outf("output.txt");
}
