#include <fstream>
#include <queue>
#include <algorithm>

bool comparator(const std::pair<int, int>& v1, const std::pair<int, int>& v2)
{
    if (v1.first < v2.first)
        return false;
    if (v1.first > v2.first)
        return true;
    if (v1.second < v2.second)
        return false;
    if (v1.second > v2.second)
        return true;
}

int main()
{
    std::ifstream inf ("input.txt");

    unsigned int count_elements, count_operations;
    inf >> count_elements >> count_operations;

    std::pair<int, int> heap_min[count_elements];

    for(int i = 0; i < count_elements; ++i)
    {
        inf >> heap_min[i].first;
        heap_min[i].second = i + 1;
    }
    inf.close();
    std::make_heap(&heap_min[0], &heap_min[count_elements], comparator);

    int lastIndex = count_elements - 1;

    for(int i = 0; i < count_operations; ++i)
    {
        int sum = 0; // 2 * 10^4
        for(int j = 0; j < 2; ++j)
        {
            sum += heap_min[0].first;
            std::pop_heap(&heap_min[0], &heap_min[count_elements - j], comparator);
        }

        const unsigned int end_index = count_elements - 2;
        lastIndex ++;

        heap_min[end_index] = std::pair<int, int>(sum, lastIndex);

        if (i + 1 != count_operations)
            std::push_heap(&heap_min[0], &heap_min[end_index + 1], comparator);
        count_elements --;
    }

    std::ofstream outf ("output.txt");

    for(int i = 0; i < count_elements; i++)
    {
        outf << heap_min[i].first << " ";
    }
}
