#include <iostream>
using namespace std;

//unsigned char lexicon []{1, 2, 3, 4, 5, 6, 7, 8};
// from 0 to lastChar

void print(string& line, int endIndex, int beginIndex = 0)
{
    cout << line[beginIndex];
    for(int i = beginIndex + 1; i <= endIndex; i++)
    {
        cout << " " << line[i];
    }
    cout << endl;
}

void permutations(string& line, unsigned short indexLastChar, unsigned short indexFirstChar = 0)
{
    if(indexFirstChar == indexLastChar)
    {
        print(line, indexLastChar);
    }
    else
    {
        for (unsigned short index = indexFirstChar; index <= indexLastChar; index++)
        {
            int j = index;
            for(int i = index - 1; i >= indexFirstChar; i--)
            {
                swap(line[i], line[j]);
                j --;
            } // Прокручивание всех цифр для лексикографического порядка
            permutations(line, indexLastChar, indexFirstChar + 1);
            j = indexFirstChar;
            for(int i = indexFirstChar + 1; i<= index; i++)
            {
                swap(line[i], line[j]);
                j ++;
            } // Реверс прокручивание
        }
        /*Циклы нужны для следующих ситуаций:
            Необходимо поменять местами 1 и 3 в 123. Но если сделать простой `swap`, то будет не лексикографический порядок.
            Поэтому нам нужно 123 превратить в 312. А потом обратно в 123.*/
    }
}

int main()
{
    unsigned short countNums;
    cin >> countNums;
    string lexicon = "12345678";

    permutations(lexicon, countNums - 1);
}
// Сначала выводит 321, а потом 312. НЕПРАВИЛЬНО!
