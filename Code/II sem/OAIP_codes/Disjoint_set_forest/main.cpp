#include <iostream>
#include <vector>
#define vec std::vector
#define pr std::pair

template<typename type>
struct DSF
{
private:
    // Номер родительского массива - элемент
    vec<pr<unsigned int, type>> mass_elements;
    unsigned int size;

    int get_private(int index_item)
    {
        if (mass_elements[index_item].first != index_item)
        {
            mass_elements[index_item].first = get_private(mass_elements[index_item].first);
        }
        return mass_elements[index_item].first;
    }

    void combine_private(const unsigned int& child_index, const unsigned int& parent_index)
    {
        mass_elements[child_index].first = parent_index;
    }

public:

    // Изначально для каждого элемента своё множество
    DSF(const unsigned int& size, const vec<type>& elements)
    {
        this->size = size;
        mass_elements.resize(size);
        for(unsigned int index = 0; index < size; index++)
        {
            mass_elements[index].first = index;
            mass_elements[index].second = elements[index];
        }
    }

    void combine(const unsigned int& child_index, const unsigned int& parent_index)
    {
        if(child_index > size || parent_index > size)
        {
            return;
        }
        return combine_private(child_index - 1, parent_index - 1);
    }

    int get(int index_item)
    {
        if(index_item > size)
        {
            return -1;
        }
        return get_private(index_item) + 1;
    }
};

int main()
{
    vec<int> elements {1, 2, 3, 4, 5};

    DSF dsf(elements.size(), elements);
    dsf.combine(1, 0);
    dsf.combine(3, 1);
    dsf.combine(2, 3);
    std::cout << dsf.get(2) + 1 << std::endl;
    std::cout << dsf.get(3) + 1 << std::endl;

    return 0;
}