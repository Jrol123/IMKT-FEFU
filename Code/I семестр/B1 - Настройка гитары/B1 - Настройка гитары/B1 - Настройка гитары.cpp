#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    //Даётся отношение i + 1-й строки относительно i-й (2-я выше/ниже 1-й)
    string sStrings; // Начальная настройка струн
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> sStrings;
    cout << sStrings << endl << endl;
    char cState = '='; // Состояние всех последующих струн (если настроены ниже + выше — капут)

    int iCount = -1;

    for (int i = 0; i < sStrings.length(); i++)
    {
        iCount += 1;
        char cSign = sStrings[i]; // Статус i + 1 струны относительно  i
        if (cSign == '&')
        {
            if (sStrings[i + 1] == 'l')
            {
                cSign = '<';
            }
            else
            {
                cSign = '>';
            }
            i += 3;
        }

        if (cSign != cState && cSign != '=')
        {
            if (cState != '=')
            {
                cout << string(5 - iCount, '?');
                outf << string(5 - iCount, '?');
                break;
            }
            else
            {
                cState = cSign;
            }
        }

        switch (cState)
        {
            case '=':
            {
                cSign = '*';
                break;
            }
            case '<':
            {
                cSign = '+';
                break;
            }
            case '>':
            {
                cSign = '-';
                break;
            }
        }
        outf << cSign;
        cout << cSign;
    }

    cout << endl;
}