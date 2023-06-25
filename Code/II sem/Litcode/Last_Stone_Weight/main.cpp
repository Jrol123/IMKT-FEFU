#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int lastStoneWeight(vector<int>& stones)
{
    priority_queue max_heap (stones.begin(), stones.end());
    while (max_heap.size() > 1)
    {
        int stone1 = max_heap.top();
        max_heap.pop();
        int stone2 = max_heap.top();
        max_heap.pop();
        if (stone1 != stone2)
        {
            max_heap.push(abs(stone1 - stone2));
        }
    }
    return max_heap.empty() ? 0 : max_heap.top();
}

int main()
{
    vector<int> vc1 {2, 7, 4, 1, 8, 1};

    cout << lastStoneWeight(vc1) << endl;
}
