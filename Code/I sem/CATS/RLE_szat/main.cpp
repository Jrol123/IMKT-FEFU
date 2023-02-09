#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream outf("output.txt");

void flushSame(int length, char(&mass)[127])
{
    string output = "1 " + to_string(length) + " " + to_string(mass[0]);
    cout << output << endl;
    outf << output << endl;
}
void flushDiff(int length, char(&mass)[127])
{
    string output = "0 " + to_string(length) + " ";
    cout << output;
    outf << output;
    for(int i = 0; i < length; i++)
    {
        output = to_string(mass[i]) + " ";
        cout << output;
        outf << output;
    }
    cout << endl;
    outf << endl;
}

int main()
{
    ifstream inf("input.txt");

    char uniqueCase [127]{0};
    int countOfCase = 1;

    char symA = inf.get();
    char symB = inf.get();
    uniqueCase[0] = symA;
    bool stateOfCase = (symA == symB); // True - одинаковые. False - разные

    // Не более 255 символов в одном массиве
    // Сделать "экстренный" сброс при достижении предела
    // Обработать пустой массив (?) (можно просто методом исключений)

    while(symB != '\377')
    {
        bool nowState = (symA == symB);
        if (nowState != stateOfCase && countOfCase > 1)
        {
            // Необходимо переделать всю систему!
            //Не обязательно, что после Same идёт Diff
            if (stateOfCase)
            {
                flushSame(countOfCase, uniqueCase);
                // Не обязательно обнулять массив, если работать со счётчиком.
                stateOfCase = nowState;
                uniqueCase[0] = symB;
                if (stateOfCase)
                {
                    countOfCase = 2;
                }
                else
                {
                    countOfCase = 1;
                }
            }
            else
            {
                flushDiff(countOfCase - 1, uniqueCase);
                // Не обязательно обнулять массив, если работать со счётчиком.
                stateOfCase = nowState;
                uniqueCase[0] = symB;
                if (stateOfCase)
                {
                    countOfCase = 2;
                }
                else
                {
                    countOfCase = 1;
                }
            }
        }
        else
        {
            if (!stateOfCase)
            {
                uniqueCase[countOfCase] = symB;
            }
            countOfCase ++;
        }
        symA = symB;
        symB = inf.get();

        // Не ищет одинаковое после одинакового

        if (countOfCase == 127)
        {
            if(stateOfCase)
            {
                flushSame(countOfCase,uniqueCase);
                uniqueCase[0] = symB;
                countOfCase = 1;
            }
            else
            {
                flushDiff(countOfCase,uniqueCase);
                uniqueCase[0] = symB;
                countOfCase = 1;
            }
            symA = symB;
            symB = inf.get();
            // 100 % совпадение в начале
        } // Защита от переполнения
    }
    // Не работает (см. output.txt, первые строчки)
    inf.close();
    if (countOfCase != 0)
    {
        if(stateOfCase)
        {
            flushSame(countOfCase,uniqueCase);
        }
        else
        {
            flushDiff(countOfCase, uniqueCase);
        }
    }

    // Вывод цепочек в двоичном виде.

    // Формат цепочек:
    // Сначала идут управляющие биты + длина цепочки (1 + 7 бит) Затем идут элементы цепочки
    //
    // Не получается вывод в файл.
}