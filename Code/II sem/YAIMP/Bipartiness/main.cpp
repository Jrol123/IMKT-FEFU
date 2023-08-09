#include <iostream>
#include <vector>
using namespace std;

bool is_bipartite = true;

void dfs(const vector<vector<bool>>& graph, vector<int> &colored, const unsigned int index_vertex, const unsigned int& count_vertex)
{
    for (int column = 0; column < count_vertex; column++)
    {
        if ((graph[index_vertex][column] && colored[column] == 0))
        {
            colored[column] = colored[index_vertex] == 1 ? 2 : 1;
            if (is_bipartite)
                dfs(graph, colored, column, count_vertex);
            else
                return;
        }
        else if (is_bipartite &&
        graph[index_vertex][column] && colored[column] != 0 &&
        colored[column] == colored[index_vertex])
        {
            cout << "NO";
            is_bipartite = false;
            return;
        }
    }
}

int main()
{
    int count_vertex;
    cin >> count_vertex;

    vector<vector<bool>> graph(count_vertex, vector<bool>(count_vertex, false));
    // ¬вод массива
    for (int row = 0; row < count_vertex; row++)
    {
        for (int column = 0; column < count_vertex; column++)
        {
            bool state_vertex;
            cin >> state_vertex;
            graph[row][column] = state_vertex;
        }
    }

    vector<int> color_vertex(count_vertex);
    color_vertex[0] = 1;
    dfs(graph, color_vertex, 0, count_vertex);

    if (is_bipartite)
        cout << "YES";

    return 0;
}
/*
8
0 0 0 0 1 1 0 0
0 0 0 0 1 0 1 0
0 0 0 1 0 1 0 1
0 0 1 0 0 0 0 0
1 1 0 0 0 0 0 0
1 0 1 0 0 0 0 0
0 1 0 0 0 0 0 0
0 0 1 0 0 0 0 0

5
0 1 1 0 0
1 0 0 1 0
1 0 0 1 0
0 1 1 0 1
0 0 0 1 0

8
0 1 0 0 1 1 0 0
1 0 0 0 1 0 1 0
0 0 0 1 0 1 0 1
0 0 1 0 0 0 0 0
1 1 0 0 0 0 1 0
1 0 1 0 0 0 0 0
0 1 0 0 1 0 0 0
0 0 1 0 0 0 0 0
*/