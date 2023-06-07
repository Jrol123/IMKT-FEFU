#include <fstream>
#include <vector>
#define vec std::vector
/*
 * Попробовать вставить
 */

int main()
{
    std::ifstream inf("input.txt");

    int count_RC;
    inf >> count_RC;
    vec<vec<int>> matrix_smezhn_const (count_RC, vec<int>(count_RC));
    vec<vec<int>> matrix_smezhn_work (count_RC, vec<int>(count_RC));

    for(int row = 0; row < count_RC; row++)
    {
        for(int collumn = 0; collumn < count_RC; collumn++)
        {
            int element;
            inf >> element;
            matrix_smezhn_const[row][collumn] = element;
            matrix_smezhn_work[row][collumn] = element;
        }
    }
    inf.close();

    int state_checks [2][count_RC]; // 0 - столбцы, 1 - строки
    for(int st = 0; st < 2; st++)
    {
        for(int t = 0; t < count_RC; t++)
        {
            state_checks[st][t] = 0;
        }
    } // Инициализация state_checks

    for(int row = 0; row < count_RC; row++)
    {
        int min_num = INT_MAX;
        for(int collumn = 0; collumn < count_RC; collumn++)
        {
            min_num = std::min(min_num, matrix_smezhn_work[row][collumn]);
        }
        for(int collumn = 0; collumn < count_RC; collumn++)
        {
            matrix_smezhn_work[row][collumn] -= min_num;
        }
    } // Построчное отнимание минимумов


    for(int collumn = 0; collumn < count_RC; collumn++)
    {
        int min_num = INT_MAX;
        bool state = true;
        for(int row = 0; row < count_RC; row++)
        {
            min_num = std::min(min_num, matrix_smezhn_work[row][collumn]);
            if (min_num == 0)
            {
                state = false;
                break;
            }
        }
        if (state)
        {
            for (int row = 0; row < count_RC; row++)
            {
                matrix_smezhn_work[row][collumn] -= min_num;
            }
        }
    } // Постолбцовое отнимание минимумов



    std::ofstream outf("output.txt");
}
