#include <fstream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

void DFS(int st, vector<int> adj_matrix[], int visited[])
{
    visited[st] = 1;

    for (int r : adj_matrix[st])
    {
        if (visited[r] == 0)
        {
            DFS(r, adj_matrix, visited);
        }
    }
}

int main() {
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    int count_vertex, count_edge;
    inf >> count_vertex >> count_edge;

    if (count_vertex - count_edge != 1)
    {
        outf << "NO" << endl;
        exit(0);
    }

    vector<int> adj_matrix[count_vertex + 1];
    int visited[count_vertex + 1] = {};

    for (int i = 0; i < count_edge; i++)
    {
        int vertex_a, vertex_b;
        inf >> vertex_a >> vertex_b;
        adj_matrix[vertex_a].push_back(vertex_b);
        adj_matrix[vertex_b].push_back(vertex_a);
    }

    inf.close();

    DFS(1, adj_matrix, visited);

    bool is_connected = true;
    for (int i = 1; i <= count_vertex; i++)
    {
        if (visited[i] == 0)
        {
            is_connected = false;
            break;
        }
    }

    if (is_connected)
    {
        outf << "YES" << endl;
    }
    else
    {
        outf << "NO" << endl;
    }

    return 0;
}