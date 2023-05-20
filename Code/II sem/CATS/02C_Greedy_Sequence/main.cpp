#include <fstream>
#include <queue>

// необходимо сделать устойчивую кучу?

int main()
{
    std::ifstream inf ("input.txt");

    unsigned int count_elements, count_operations;
    inf >> count_elements >> count_operations;

    int mass_elements[count_elements];

    for(int i = 0; i < count_elements; ++i)
    {
        inf >> mass_elements[i];
    }
    inf.close();

    std::make_heap(&mass_elements[0], &mass_elements[count_elements], std::greater<int>());
    for(int i = 0; i < count_operations; ++i)
    {
        int sum = 0; // 2 * 10^4
        for(int j = 0; j < 2; ++j)
        {
            sum += mass_elements[0];
            std::pop_heap(&mass_elements[0], &mass_elements[count_elements - j], std::greater<int>());
        }

        const unsigned int end_index = count_elements - 2;
        mass_elements[end_index] = sum;

        std::push_heap(&mass_elements[0], &mass_elements[end_index + 1], std::greater<int>());
        count_elements --;
    }

    std::ofstream outf ("output.txt");

    for(int i = 0; i < count_elements; i++)
    {
        outf << mass_elements[i] << " ";
    }
}
