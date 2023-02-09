#include <iostream>
using namespace std;

char Changer(char cChar)
{
    int iChar = int(cChar);
    if ((90 >= iChar && iChar >= 65) || (122 >= iChar && iChar >= 97))
    {
        return (char)(cChar ^ (1 << 5));
    }
    else
    {
        return (char)(cChar);
    }
}

int main()
{
    char cChar;
    cin >> cChar;

    cout << Changer(cChar);
}