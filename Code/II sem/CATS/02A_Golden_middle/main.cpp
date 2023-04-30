//#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    ifstream inf("input.txt");
    int countOfElements;
    inf >> countOfElements;
    priority_queue<int, vector<int>, less<int>> maxHeap; // Левая половина
    priority_queue<int, vector<int>, greater<int>> minHeap; // Правая половина

    ofstream outf("output.txt");

    int element;
    inf >> element;
    maxHeap.push(element);
    outf << element << endl;

    for(int index = 1; index < countOfElements; ++index)
    {
        inf >> element;

        if(maxHeap.size() > minHeap.size())
        {
            if(element < maxHeap.top())
            {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
                maxHeap.push(element);
            } // Балансировка (т. к. будет перекос на 2 элемента)
            else
            {
                minHeap.push(element);
            }
            outf << maxHeap.top() << endl;
        } // Если слева кол-во элементов больше на 1
        else
        {
            if(element > minHeap.top())
            {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(element);
            } // Балансировка (т. к. будет перекос на 2 элемента)
            // Проблем с перекосом не будет, т. к. даже если количество элементов одинаковое,
            // то на следующем цикле всё зайдёт в верхний if
            else
            {
                maxHeap.push(element);
            }
            outf << maxHeap.top() << endl;
        } // Если справа <= элементов, чем слева
    }

    inf.close();
    outf.close();
}
