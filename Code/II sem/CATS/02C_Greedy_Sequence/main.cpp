#include <fstream>

// необходимо сделать устойчивую кучу?

// Честно, я не понимаю зачем тут вообще нужно сохранение индексов.
// "Если наименьших чисел более двух, следует выбрать числа с наименьшими номерами в последовательности".
// И ЕСЛИ ТАКИХ МИНИМАЛЬНЫХ ЧИСЕЛ ДВОЕ, ТО ОНИ ПО-ЛЮБОМУ ПОПАДУТ В "ГОЛОВУ"!

// Сравнивать по-индексам

// Компаратор: Сортировка по возрастанию по значению, потом по индексу

void siftUpMin(int mass [], int massIndexes[], int massOrigin[], int index)
{
    while(mass[index] < mass[(index - 1) / 2])
    {
        std::swap(mass[index], mass[(index - 1) / 2]);
        std::swap(massIndexes[index],massIndexes[(index - 1) / 2]);
        std::swap(massOrigin[massIndexes[index]], massOrigin[massIndexes[(index - 1) / 2]]);
        index = (index - 1) / 2;
    }
}

void siftDownMin(int mass [], int massIndexes[],int massOrigin[], int index, const int& countEl)
{
    while (2 * index + 1 < countEl)
    {
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;

        int subIndex = leftIndex;
        if(rightIndex < countEl and mass[rightIndex] < mass[leftIndex])
        {
            subIndex = rightIndex;
        } // Выбор наименьшего ребёнка
        if(mass[index] < mass[subIndex])
        {
            break;
        } // Если всё в порядке
        std::swap(mass[index], mass[subIndex]);
        std::swap(massIndexes[index],massIndexes[subIndex]);
        std::swap(massOrigin[massIndexes[index]], massOrigin[massIndexes[subIndex]]);
        index = subIndex; // Индекс меняемого элемента
    }
}

void popHeapMin(int mass [], int massIndexes [], int massOrigin[], const int& countEl)
{
    std::swap(mass[0], mass[countEl - 1]);
    std::swap(massIndexes[0],massIndexes[countEl - 1]);
    std::swap(massOrigin[massIndexes[0]], massOrigin[massIndexes[countEl - 1]]);

    siftDownMin(mass, massIndexes, massOrigin, 0, countEl - 1);
}

void buildHeapMin(int mass [], int massIndexes [], int massOrigin[], const int& countEl)
{
    for(int i = countEl / 2; i >= 0; --i)
    {
        siftDownMin(mass, massIndexes, massOrigin, i, countEl);
    }
}

int main()
{
    std::ifstream inf ("input.txt");

    unsigned int count_elements, count_operations;
    inf >> count_elements >> count_operations;

    int heap_min[count_elements];
    int mass_indexes [count_elements], mass_origin [count_elements];

    for(int i = 0; i < count_elements; ++i)
    {
        inf >> heap_min[i];
        mass_indexes[i] = i;
        mass_origin[i] = i;
    }
    inf.close();

    buildHeapMin(heap_min, mass_indexes, mass_origin, count_elements);

    for(int i = 0; i < count_operations; ++i)
    {
        int sum = 0; // 2 * 10^4
        for(int j = 0; j < 2; ++j)
        {
            sum += heap_min[0];
            popHeapMin(heap_min, mass_indexes, mass_origin, count_elements - j);
//            std::pop_heap(&heap_min[0], &heap_min[count_elements - j], std::greater<int>());
        }

        const unsigned int end_index = count_elements - 2;
        heap_min[end_index] = sum;

        siftUpMin(heap_min, mass_indexes, mass_origin, end_index);
//        std::push_heap(&heap_min[0], &heap_min[end_index + 1], std::greater<int>());
        count_elements --;
    }

    std::ofstream outf ("output.txt");

    for(int i = 0; i < count_elements; i++)
    {
        outf << heap_min[i] << " ";
    }
}
