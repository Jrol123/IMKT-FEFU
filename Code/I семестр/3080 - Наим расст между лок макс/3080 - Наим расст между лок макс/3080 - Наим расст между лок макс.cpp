#include <iostream>
#include <limits>
using namespace std;
// обнулять iLenMin!!!
// расстояние между цифрами + 1
//
//локальный максимум - это максимум по сравнению с двумя соседними элементами
int main()
{
    const int iMaxRangeNum = numeric_limits<int>::max();
    int iLengthNow = 0; // количество пройденных цифр от последнего максимума
    int iLengthMin = iMaxRangeNum; // минимальное расстояние между максимумами
    int iNum1, iNum2, iNum3; // оперируемые числа
    int iCountOfMax = 0; // Количество локальных максимумов

    cin >> iNum1 >> iNum2;
    if (iNum2 != 0)
    {
        cin >> iNum3;
        while (iNum3 != 0)
        {
            if (iNum1 < iNum2 && iNum2 > iNum3)
            {
                iLengthNow += 1;
                if (iLengthNow < iLengthMin && iLengthNow > 1)
                {
                    iLengthMin = iLengthNow;
                }
                iCountOfMax++;
                iLengthNow = 0;
            }
            else if (iCountOfMax > 0)
            {
                iLengthNow += 1;
            }
            iNum1 = iNum2; iNum2 = iNum3; cin >> iNum3;
        }
    }
    cout << ((iCountOfMax > 1) ? iLengthMin : 0);
}