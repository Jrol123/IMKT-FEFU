#include <iostream>
#include <set>
using namespace std;

// ѕроверка на количество уникальных знаков?

void inserter(set<char>& set, const string& str)
{
    for(char character : str)
    {
        set.insert(character);
    }
}

bool isIsomorphic(string s, string t)
{
    set<char> freq_set1, freq_set2;

    inserter(freq_set1, s);
    inserter(freq_set2, t);

    return freq_set1.size() == freq_set2.size();
}

int main()
{
    string
    s1 = "egg", t1 = "add",
    s2 = "foo", t2 = "bar",
    s3 = "paper", t3 = "title";

    cout << isIsomorphic(s1, t1) << endl;
    cout << isIsomorphic(s2, t2) << endl;
    cout << isIsomorphic(s3, t3) << endl;
}
