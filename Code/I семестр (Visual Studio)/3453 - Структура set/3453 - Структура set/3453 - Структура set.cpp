#include <iostream>
#include <set>
using namespace std;
// COUNT - кол-во уникальных элементов в массиве
// PRESENT <int> - есть ли значение в массиве
// ADD <int> - добавить значение в массив
int main()
{
    int iCountOfRequests; // Количество вводимых команд
    set <int> iMass;
    cin >> iCountOfRequests;

    for (int i = 0; i < iCountOfRequests; i++)
    {
        string sRequest; // Значение запроса
        cin >> sRequest;
        if (sRequest == "COUNT")
        {
            cout << iMass.size() << endl;
        }
        else if (sRequest == "PRESENT")
        {
            int iNum;
            cin >> iNum;
            cout << (iMass.find(iNum) != iMass.end()? "YES" : "NO") << endl; // find() возвращает указатель на номер ячейки или на номер конца массива (end) // Эти выражения не равны друг другу
            // Можно было бы сделать через count()
        }
        else
        {
            int iNum;
            cin >> iNum;
            iMass.insert(iNum);
        }
    }
}