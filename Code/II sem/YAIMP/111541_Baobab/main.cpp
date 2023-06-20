#include <iostream>
using namespace std;

int countVertex;
bool matrix_smezhn[100][100];
bool matrix_ifVisited[100];

void dfs(int vertex, int parent)
{
    matrix_ifVisited[vertex] = true;

    for (int i = 0; i < countVertex; i++)
    {
        if (matrix_smezhn[vertex][i])
        {

            if (i == parent) continue;

            if (matrix_ifVisited[i])
            {
                cout << "NO";
                exit(0);
            }
            dfs(i, vertex);
        }
    }
}

int main()
{
    cin >> countVertex;

    for (int row = 0; row < countVertex; row++)
    {
        for (int column = 0; column < countVertex; column++)
        {
            cin >> matrix_smezhn[row][column];
        }
    }

    dfs(0, -1);

    for (int i = 0; i < countVertex; i++)
    {
        if (!matrix_ifVisited[i])
        {
            cout << "NO";
            return 0;
        }
    }

    cout << "YES";
}