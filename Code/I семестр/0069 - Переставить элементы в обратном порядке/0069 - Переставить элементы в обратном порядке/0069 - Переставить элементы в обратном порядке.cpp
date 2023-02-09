#include <iostream>
#include <vector>
using namespace std;
// можно использовать функцию rbegin()
int main()
{
    int iCountOfNums; // Количество чисел
    vector <int> iMass; // Массив чисел
    cin >> iCountOfNums;
    for (int i = 0; i < iCountOfNums; i++)
    {
        int iNum;
        cin >> iNum;
        iMass.push_back(iNum);
    }
    string s (iMass.rbegin(), iMass.rend());
    cout << s;
}