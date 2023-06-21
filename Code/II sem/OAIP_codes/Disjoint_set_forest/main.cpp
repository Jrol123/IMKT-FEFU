#include <iostream>
#include <vector>
#define vec std::vector

template<typename type>
struct DSF
{
    vec<std::pair<int, type>> mass; // Множество деревьев + множество рангов. Содержит родителей.

    type minElement;
    DSF(const int size, const vec<type>& elements)
    {
        mass.resize(size);
        minElement = elements[0];
        for (int index = 0; index < size; ++index)
        {
            mass[elements[index] - minElement] = new Node(elements[index]);
        }
    }

    type get(type val)
    {
        if(mass[val]->val != val)
        {
            mass[val]->val = get(mass[val]->val);
        }
        return mass[val]->val;
    }

    void conjoin(type val1, type val2)
    {

    }
};

int main()
{
    vec<int> elements {1, 2, 3, 4, 5};

    DSF dsf(elements.size(), elements);
    dsf.get(1);

    return 0;
}
