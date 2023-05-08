#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

const long long COUNT = 100000000;

void bubbleSort(int mass[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (mass[j] > mass[j + 1])
            {
                std::swap(mass[j], mass[j + 1]);
//                int temp = mass[j];
//                mass[j] = mass[j + 1];
//                mass[j + 1] = temp;
            }
        }
    }
}

void siftDownMax(int mass[], int index, int countEl) {
    while (2 * index + 1 < countEl) {
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;

        int subIndex = leftIndex;
        if (rightIndex < countEl and mass[rightIndex] > mass[leftIndex]) {
            subIndex = rightIndex;
        } // Выбор наименьшего ребёнка
        if (mass[index] >= mass[subIndex]) {
            break;
        } // Если всё в порядке
        swap(mass[index], mass[subIndex]);
        index = subIndex; // Индекс меняемого элемента
    }
}

void buildHeapMax(int mass[], int countEl) {
    for (int i = countEl / 2; i >= 0; --i) {
        siftDownMax(mass, i, countEl);
    }
}

void heap_sort(int mass[], int countEl) {
    buildHeapMax(mass, countEl);

    for (int i = countEl - 1; i >= 0; i--) {
        swap(mass[0], mass[i]);
        siftDownMax(mass, 0, i);
    }
}

int main() {
    int experiments = 10;

    double sumTime = 0;

    for (int i = 0; i < experiments; i++) {
        int *mass = new int[COUNT];
        for (int j = 0; j < COUNT; j++) {
            mass[j] = rand() % 100;
        }

        clock_t start = clock();

//        heap_sort(mass, COUNT);
        bubbleSort(mass, COUNT);
        clock_t end = clock();

        delete[] mass;

        double time = ((double)(end - start)) / CLOCKS_PER_SEC;
        sumTime += time;

        cout << "Time " << i + 1 << ": " << fixed
             << setprecision(6) << time << endl;
    }

    double averageTime = sumTime / experiments;

    cout << "Total time: " << fixed << setprecision(6)
         << averageTime << endl;

    return 0;
}