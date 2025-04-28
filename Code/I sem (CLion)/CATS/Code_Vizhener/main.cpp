//#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

static const int countVocSym = 34;
using namespace std;
// 33 буквы в алфавите + 1 пробел
int main()
{
    setlocale(LC_ALL, "Russian"); // Алфавит не сработал
    // проверить 0001_bit_chet на вывод в консоль
    // setlocale(LC_ALL, "ru_RU.utf-8");
    ifstream inf ("input.txt");
    ofstream outf ("output.txt");

    unsigned char alphabet [countVocSym] = {'0'};

    for(int i = 192; i <= 192 + 5; i ++ )
    {
        alphabet[i % 192] = i;
    }
    alphabet[6] = 168;
    for(int i = 192 + 6 + 1; i <= 192 + 31 + 1; i ++ )
    {
        alphabet[i % 192] = i - 1;
    }
    alphabet[33] = ' ';

    vector <int> migrator;
    /*
    string toTransfer;
    getline(inf, toTransfer);
    stringstream ss;
    ss << toTransfer; // Перевод строки в поток. По-моему, есть более простой способ, но...

    while(!ss.eof())
    {
        int a;
        ss >> a;
        migrator.push_back(a);
    }
    ss.clear();
    toTransfer.clear();
    */
    string keyString;
    getline(inf, keyString);
    for(int i = 0; keyString[i] != '\0'; i++)
    {
        unsigned char sym = keyString[i];
        if (sym == 168)
        {
            sym = 7 - 1;
        }
        else if (sym == ' ')
        {
            sym = 33 - 1;
        }
        else if (sym >= (192 + 7))
        {
            sym  = sym % 192 + 1;
        }
        else
        {
            sym %= 192;
        }
        migrator.push_back(sym);
    }
    // CORRECT

    unsigned char sym = inf.get();
    for(int i = 0; sym != 255; i++)
    {
        int migrationIndex = migrator[i % migrator.size()];
        if (sym == 168)
        {
            sym = alphabet[(6 + migrationIndex) % countVocSym];
        }
        else if (sym >= (192 + 7))
        {
            sym = alphabet[(sym % 192 + 1 + migrationIndex) % countVocSym];
        }
        else if (sym == ' ')
        {
            sym = alphabet[(33 + migrationIndex)%countVocSym];
        }
        else
        {
            sym = alphabet[(sym % 192 + migrationIndex) % countVocSym];
        }
        outf << sym;
//        cout << sym;
        sym = inf.get();
    }
}
