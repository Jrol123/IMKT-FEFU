#include <iostream>
#include <vector>
using namespace std;

int Merger(int iLeft, int iRight, char cSym)
{
    switch (cSym)
    {
        case '+':
        {
            return iLeft + iRight;
        }
        case '-':
        {
            return iLeft - iRight;
        }
        case '*':
        {
            return iLeft * iRight;
        }
        case '/':
        {
            return iLeft / iRight;
        }
    }
}

// Нам неважен порядок. Для корректной работы проги необходимо сразу применять действия. (Как я понял)
// Необходимо учесть то, что символы добавляются постепенно. Соотвтетственно должно быть несколько "левых" частей.
// Можно сделать 2 функции. Одну основную, другую для счёта "доп числа" (правого числа).

int main()
{
    char cSym;
    cin >> cSym;
    int imMass [75] {1, int(cSym) - 48}; // Для оптимизации памяти
    cin.get();

    do
    {

        cSym = cin.get();
        int iSym = int(cSym) - 48;
        int iLength = imMass[0];

        if (0 <= iSym && iSym <= 9)
        {
            imMass[iLength + 1] = int(cSym) - 48;
            imMass[0] += 1;
        }
        else
        {
            imMass[iLength - 1] = Merger(imMass[iLength - 1], imMass[iLength], cSym);
            imMass[0] -= 1;
        }
        cSym = cin.get();
    }while(cSym != '\n');

    cout << imMass[1];
}
// В корне неверный принцип решения!
// Всё-таки придётся делать массив...