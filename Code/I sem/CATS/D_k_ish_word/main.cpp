#include <iostream>
#include <vector>
//#include <fstream>
using namespace std;

int main()
{
    vector<string> massWords;
    string word;
    char nextSym = ' ';
    int countOfWords = 0;

    for(int i = 0; nextSym == ' '; i++)
    {
        countOfWords ++;
        cin >> word;
        massWords.push_back(word);
        nextSym = cin.get();
    }
//    free(*nextSym);
    int indexOfWord = cin.get() - 48;

    if (indexOfWord > countOfWords)
    {
        cout << massWords[countOfWords - 1];
    }
    else
    {
        cout << massWords[indexOfWord - 1];
    }
}
