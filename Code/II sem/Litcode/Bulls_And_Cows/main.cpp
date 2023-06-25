#include <iostream>
#include <string>
#include <vector>
using namespace std;

string getHint(string secret, string guess)
{
    const string div1 = "A";
    const string div2 = "B";
    const unsigned char minDigit = '0';

    int bulls = 0;
    int cows = 0;
    vector<int> secret_count(10, 0);
    vector<int> guess_count(10, 0);

    for (int i = 0; i < secret.size(); i++)
    {
        const unsigned char secret_char = secret[i];
        const unsigned char guess_char = guess[i];
        if (secret_char == guess_char)
        {
            bulls++;
        }
        else
        {
            secret_count[secret_char - minDigit]++;
            guess_count[guess_char - minDigit]++;
        }
    }

    for (int i = 0; i <= 9; i++)
    {
        cows += min(secret_count[i], guess_count[i]);
    }

    return to_string(bulls) + div1 + to_string(cows) + div2;
}

int main()
{
    string
    sc1 = "1807", gs1 = "7810",
    sc2 = "1123", gs2 = "0111";

    cout << getHint(sc1, gs1) << endl;
    cout << getHint(sc2, gs2) << endl;
}
