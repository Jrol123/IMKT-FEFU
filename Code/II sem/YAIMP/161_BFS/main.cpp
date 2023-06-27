#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool border_check(const pair<int, int>& pr, const unsigned int& border)
{
    bool first = (0 <= pr.first && pr.first < border);
    bool second = (0 <= pr.second && pr.second < border);
    return first & second;
}

void reversed_bfs(const pair<int, int>& begin_square, vector<vector<int>> distance_matrix, vector<int> &ans, const unsigned int& size)
{
    pair<int, int>move_list[8] {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}};

    ans.push_back(begin_square.first);
    ans.push_back(begin_square.second);
    int left_len = distance_matrix[begin_square.first][begin_square.second] - 1;
    pair<int, int> cur_point = begin_square;
    while (left_len > 0)
    {
        for (auto & current_move : move_list)
        {
            pair<int, int> next_point {cur_point.first + current_move.first, cur_point.second + current_move.second};
            if (!(border_check(next_point, size) && distance_matrix[next_point.first][next_point.second] == left_len))
                continue;
            ans.push_back(next_point.first);
            ans.push_back(next_point.second);
            cur_point = next_point;
            left_len--;
            break;
        }
    }
}

void bfs(pair<int, int> begin_square, pair<int, int> end_square, const unsigned int& size)
{
    queue<pair<int, int>> bfs_queue;
    vector<vector<int>> distance_matrix(size, vector<int>(size, __INT_MAX__));

    // Список всех ходов.
    pair<int, int>move_list[8] {{-2, -1}, {-1, -2}, {1, -2}, {2, -1},
                                {-2, 1}, {-1, 2}, {1, 2}, {2, 1}};

    // Начальный пуш.
    bfs_queue.push(begin_square);
    distance_matrix[begin_square.first][begin_square.second] = 0;
    // Стандартный BFS.
    while (!bfs_queue.empty())
    {
        pair<int, int> point = bfs_queue.front();
        bfs_queue.pop();
        for (auto & current_move : move_list)
        {
            pair<int, int> next_point {point.first + current_move.first, point.second + current_move.second};
            if (!(border_check(next_point, size) &&
                  distance_matrix[next_point.first][next_point.second] > distance_matrix[point.first][point.second] + 1))
                continue;
            distance_matrix[next_point.first][next_point.second] = distance_matrix[point.first][point.second] + 1;
            bfs_queue.push(next_point);
        }
    }

    //Дистанция до финальной клетки
    int final_distance = distance_matrix[end_square.first][end_square.second];
    cout << final_distance << endl;

    vector<int> ans;
    reversed_bfs(end_square, distance_matrix, ans, size);

    cout << begin_square.first + 1 << " " << begin_square.second + 1 << endl;
    for (int index = ans.size() - 1; index > 0; index -= 2)
    {
        cout << ans[index - 1] + 1 << " " << ans[index] + 1 << endl;
        if (ans[index - 1] == end_square.first && ans[index] == end_square.second)
            break;
    }
}

int main()
{
    int len_side;
    pair<int, int> begin_square, end_square;
    cin >> len_side >> begin_square.first >> begin_square.second >> end_square.first >> end_square.second;

    begin_square.first -= 1, begin_square.second -= 1;
    end_square.first -= 1, end_square.second -= 1;
    bfs(begin_square, end_square, len_side);

    return 0;
}