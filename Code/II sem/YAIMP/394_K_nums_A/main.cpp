#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * @brief Венгерский алгоритм для поиска минимального решения.
 *
 * @param count_problems Количество задач.
 * @param init_matrix Начальная матрица.
 * @return Матрицу координат пересечений.
 */
vector<pair<int, int>> Kuhn_Mankres(const unsigned int& count_problems, const vector <vector <int>>& init_matrix)
{
    /// Минимальные значения для строк
    vector<int> min_row(count_problems, 0);
    /// Минимальные значения для столбцов.
    vector<int> min_column(count_problems, 0);
    /// Индексы выделенных строк.
    vector<int> marked_indexes(count_problems, -1);

    for (int row = 0; row < count_problems; row++)
    {
        /// Индексы выделенных столбцов.
        vector<int> visited_column(count_problems, -1);
        /// Минимальные значения для невыделенных столбцов.
        vector<int> unmarked_column_min(count_problems, __INT_MAX__);
        /// Посещённые столбцы.
        vector<bool> visited(count_problems, false);

        /// Выделенная строка.
        int marked_row = row;
        /// Выделенный столбец.
        int marked_column = -1;
        /// Столбец с наименьшим значением.
        int min_index_column;

        // Пока не обошли все столбцы.
        while (marked_row != -1)
        {
            min_index_column = -1;

            // Поиск минимальных значений для столбцов.
            for (int column = 0; column < count_problems; column++)
            {
                if (visited[column])
                    continue;

                /**
                 * @brief Разница между элементом и минимальным значением.
                 *
                 * Используется для определения того, насколько выгодно назначить работнику некоторую задачу.
                 */
                int delta = init_matrix[marked_row][column] - min_row[marked_row] - min_column[column];

                // Сохраняем минимальное значение для текущего столбца.
                if (delta < unmarked_column_min[column])
                {
                    unmarked_column_min[column] = delta;
                    visited_column[column] = marked_column;
                }

                // Поиск наименьшего значения.
                if (min_index_column == -1 || delta < unmarked_column_min[min_index_column])
                    min_index_column = column;
            }

            // Изменение меток.
            int diff = unmarked_column_min[min_index_column];

            // Изменение метки строк и столбцов
            for (int column = 0; column < count_problems; column++)
            {
                if(!visited[column])
                    unmarked_column_min[column] -= diff;

                min_row[marked_indexes[column]] += diff;
                min_column[column] -= diff;
            }

            // Выделяем новую строку и столбец
            min_row[row] += diff;
            visited[min_index_column] = true;
            marked_column = min_index_column;
            marked_row = marked_indexes[min_index_column];
        }

        // Обновление выделенных строк.
        for (; visited_column[min_index_column] != -1; min_index_column = visited_column[min_index_column])
            marked_indexes[min_index_column] = marked_indexes[visited_column[min_index_column]];
        marked_indexes[min_index_column] = row;
    }

    /// Вектор пар назначений.
    vector<pair<int, int>> pair_comb;

    // Вывод
    for (int j = 0; j < count_problems; j++)
    {
        if (marked_indexes[j] != -1)
        {
            pair_comb.push_back(pair<int, int>(marked_indexes[j], j));
        }
    }

    return pair_comb;
}

int main()
{
    // Инициализация.

    /// Количество задач.
    unsigned int count_problems;
    /// Матрица.
    vector <vector <int>> matrix;

    cin >> count_problems;

    // Ввод матрицы.
    for (int row = 0; row < count_problems; row++)
    {
        matrix.push_back(vector<int>());

        for (int column = 0; column < count_problems; column++)
        {
            int tmp;
            cin >> tmp;
            matrix[row].push_back(--tmp);
        }
    }
    /// Вектор пар назначений.
    vector<pair<int, int>> pair_comb = Kuhn_Mankres(count_problems, matrix);
    /// Конечный результат.
    unsigned int result = 0;

    // Вывод.
    for (unsigned int index = 0; index < pair_comb.size(); index++)
    {
        result += matrix[pair_comb[index].first][pair_comb[index].second] + 1;
    }
    cout << result << endl;
}
