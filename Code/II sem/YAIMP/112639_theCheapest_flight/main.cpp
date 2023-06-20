#include <iostream>
#include <limits>

static const int max_count_vertex = 9;
using namespace std;

int weight_matrix[max_count_vertex][max_count_vertex],
        way[max_count_vertex], best_way[max_count_vertex],
        count_vertex, count_flights, best_cost = INT_MAX;
bool visited_matrix[max_count_vertex];

// Если есть возможность добраться до точки +И+ она не посещена.
bool able_to_get_to(const int& cur_vertex, const int& index_vertex)
{
    bool is_visited = !visited_matrix[index_vertex];
    bool is_way = weight_matrix[cur_vertex][index_vertex] != 0;
    return is_visited & is_way;
}

void checkCycleExistence(const int begin_vertex, int cur_vertex, int left_to_go)
{
    // Если оставшаяся дистанция = 1
    if (left_to_go == 1)
    {
        // Если из текущей вершины можно добраться до начальной
        if (weight_matrix[cur_vertex][begin_vertex] != 0)
        {
            way[count_flights] = begin_vertex;
            int way_check_vertex = begin_vertex, cur_len = 0;

            // Определение текущей стоимости пути + путь домой.
            for (int index_vertex = 1; index_vertex <= count_flights; index_vertex++)
            {
                cur_len += weight_matrix[way_check_vertex][way[index_vertex]];
                way_check_vertex = way[index_vertex];
            }

            // Если длина < наилучшей
            if (cur_len < best_cost)
            {
                best_cost = cur_len;
                for (int index_vertex = 0; index_vertex <= count_flights; index_vertex++)
                    best_way[index_vertex] = way[index_vertex];
            }
        }

        return;
    }

    visited_matrix[cur_vertex] = true;

    for (int index_vertex = begin_vertex + 1; index_vertex <= count_vertex; index_vertex++)
    {

        if (able_to_get_to(cur_vertex, index_vertex))
        {
            way[count_flights - left_to_go + 1] = index_vertex;
            checkCycleExistence(begin_vertex, index_vertex, left_to_go - 1);
        }
    }
    visited_matrix[cur_vertex] = false;
}



int main()
{
    cin >> count_vertex;

    // Ввод весовой матрицы
    for (int row = 1; row <= count_vertex; row++)
        for (int column = 1; column <= count_vertex; column++)
            cin >> weight_matrix[row][column];

    cin >> count_flights;

    for (int index_vertex = 1; index_vertex <= count_vertex; index_vertex++)
    {
        way[0] = index_vertex;
        checkCycleExistence(index_vertex, index_vertex, count_flights);
    }

    // Проверка на существование цикла
    if (best_cost == INT_MAX)
        cout << 0 << '\n';
    else
    {
        cout << best_cost << '\n';

        for (int i = 0; i <= count_flights; i++)
            cout << best_way[i] << ' ';
        cout << endl;
    }
}
