#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

  setlocale(LC_ALL, "Russian");

  unsinged string alphabet = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ ";
  string key;
  string text;
  string code;

  ifstream fin("input.txt");
  ofstream fout("output.txt");

  fin >> text >> key;

  while (key.length() < text.length())
    key += key;

  int i = 0;
  while (i < text.length()) {
      int j = 0;
      int t, k;
      while (alphabet[j]) {
          if (alphabet[j] == text[i]) {
              t = j; break;
          } j++;
      }
      j = 0;
      while (alphabet[j]) {
          if (alphabet[j] == key[i]) {
              k = j; break;
          } j++;
      }
      if ((t + k) < 33){
        code += alphabet[t + k];
      }
      if ((t + k) >= 33){
        code+= alphabet[t + k-33];
      }

      i++;
  }

  for(int i = 0; i < code.length(); i++)
    fout << code[i];

}