#include <iostream>
#include <fstream>
#include <ctime>
//#include <random>

void bubbleSort(int mass[], int size, long long& countOperations)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (mass[j] > mass[j + 1])
            {
                std::swap(mass[j], mass[j + 1]);
                countOperations ++;
            }
            countOperations ++;
        }
    }
}

void siftDownMax(int mass [], int index, int countEl, long long& countOperations)
{
    while (2 * index + 1 < countEl)
    {
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;

        int subIndex = leftIndex;
        countOperations += 3;
        if(rightIndex < countEl and mass[rightIndex] > mass[leftIndex])
        {
            subIndex = rightIndex;
            countOperations ++;
        } // Выбор наименьшего ребёнка
        countOperations += 1;
        if(mass[index] >= mass[subIndex])
        {
            countOperations += 1;
            break;
        } // Если всё в порядке
        countOperations += 1;
        std::swap(mass[index], mass[subIndex]);
        index = subIndex; // Индекс меняемого элемента
        countOperations += 2;
    }
}

void buildHeapMax(int mass [], int countEl, long long& countOperations)
{
    for(int i = countEl / 2; i >= 0; --i)
    {
        siftDownMax(mass, i, countEl, countOperations);
    }
}

void heap_sort(int mass[], int countEl, long long& countOperations)
{
    buildHeapMax(mass, countEl, countOperations);

    for(int i = countEl - 1; i >= 0; i --)
    {
        std::swap(mass[0], mass[i]); countOperations ++;
        siftDownMax(mass, 0, i, countOperations);
    }
}

int main()
{
    int len = 1;
    std::ofstream outf ("output.txt");
    std::cout << std::endl;

    for(int multiplier = 1; multiplier <= 5; multiplier++)
    {
        len *= 10;
        int *mass = new int[len];

        std::cout << multiplier << " " <<  std::endl;
        outf << multiplier << " " <<  std::endl;
        double middle = 0;

        for(int index = 1; index <= 10; index++)
        {
            std::cout <<" " << index << " ";
            outf << "try" <<" " << index << ": ";
            for (int i = 0; i < len; i++)
            {
                mass[i] = rand();
            }


//            std::clock_t start_time = std::clock();

//            bubbleSort(mass, len);
            long long countOperations = 0;
//            heap_sort(mass, len, countOperations);
            bubbleSort(mass, len, countOperations);

//            std::clock_t end_time = std::clock();



//            double time_elapsed = double(end_time - start_time) / CLOCKS_PER_SEC;
//        std::cout << time_elapsed << std::endl << std::endl;
//            outf << time_elapsed << ";   ";
            outf << countOperations << ";   ";
            middle += countOperations / 10;
        }
        delete[] mass;
        std::cout << std::endl;
        outf << "Total middle = "<< middle<< std::endl << std::endl;
    }
    outf.close();

    return 0;
}