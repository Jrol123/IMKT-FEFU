#include <iostream>
#include <vector>
using namespace std;

void dfs(const unsigned int& count_vertex, const vector<vector<bool>>& graph, vector<bool> &visited, int vertex)
{
    visited[vertex] = true;
    for (int i = 0; i < count_vertex; i++)
    {
        if (graph[vertex][i] && !visited[i])
        {
            dfs(count_vertex, graph, visited, i);
        }
    }
}

int main()
{
    int count_vertex, index_vertex, count_vertex_smezn = 0;
    cin >> count_vertex >> index_vertex;

    vector<vector<bool>> graph(count_vertex, vector<bool>(count_vertex, 0));

    bool state_vertex;
    // Ввод вершин.
    for (int row = 0; row < count_vertex; row++)
    {
        for (int column = 0; column < count_vertex; column++)
        {
            cin >> state_vertex;
            graph[row][column] = state_vertex;
        }
    }

    vector<bool> visited(count_vertex);
    dfs(count_vertex, graph, visited, index_vertex - 1);
    // Просчитывание.
    for (int i = 0; i < count_vertex; i++)
        if (visited[i])
            count_vertex_smezn++;

    cout << count_vertex_smezn;

    return 0;
}
