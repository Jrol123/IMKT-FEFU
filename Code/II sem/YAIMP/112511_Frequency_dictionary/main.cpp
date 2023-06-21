#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    map<string, int> freq;
    string word;

    while (fin >> word) {
        freq[word]++;
        if (fin.eof()) {
            break;
        }
    }

    int comp, bufernumber, counter = 0;
    string bufer;
    while (!freq.empty()){
        counter = 0;
        for (const auto& [word, count] : freq) {
            if (freq.size() == 1) {
                bufer = word;
                bufernumber = count;
                break;
            }

            if (counter == 0){
                bufer = word;
                bufernumber = count;
            }

            if (counter > 0) {
                comp = word.compare(bufer);
                if (bufernumber < count) {
                    bufer = word;
                    bufernumber = count;
                }
                if (comp < 0 && bufernumber <= count) {
                    bufer = word;
                    bufernumber = count;
                }
            }
            counter++;
        }
        fout << bufer << " " << bufernumber << endl;
        freq.erase(bufer);
    }
    return 0;
}