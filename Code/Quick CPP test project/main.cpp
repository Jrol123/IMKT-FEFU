#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int f(vector<int>& stones)
{
    // Convert stones vector to a max heap
    priority_queue<int> max_heap(stones.begin(), stones.end());

    // Smash stones until there is only one left
    while (max_heap.size() > 1)
    {
        int x = max_heap.top();
        max_heap.pop();
        int y = max_heap.top();
        max_heap.pop();
        if (x != y)
        {
            max_heap.push(y - x);
        }
    }

    // Return the last stone's weight (if there is one)
    return max_heap.empty() ? 0 : max_heap.top();
}

int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");

    vector<int> vector1 {2,7,4,1,8,1};

    cout << f(vector1);

    return 0;
}