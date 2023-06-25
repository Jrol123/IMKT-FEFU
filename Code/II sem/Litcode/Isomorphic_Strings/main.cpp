#include <iostream>
#include <map>
using namespace std;

bool isIsomorphic(string s, string t)
{
    map<char, int> s_map, t_map;

    for (int i = 0; i < s.length(); i++)
    {
        // Проверка на смещение
        if (s_map.find(s[i]) != s_map.end())
        {
            // Проверка на смещение у другого множества
            if (s_map[s[i]] != t[i])
            {
                return false;
            }
        }
        else
        {
            s_map[s[i]] = t[i];
        }

        if (t_map.find(t[i]) != t_map.end())
        {
            if (t_map[t[i]] != s[i])
            {
                return false;
            }
        }
        else
        {
            t_map[t[i]] = s[i];
        }
    }

    return true;

}

int main()
{
    string
    s1 = "egg", t1 = "add",
    s2 = "foo", t2 = "bar",
    s3 = "paper", t3 = "title",
    s4 = "bbbaaaba", t4 = "aaabbbba";

    cout << isIsomorphic(s1, t1) << endl;
    cout << isIsomorphic(s2, t2) << endl;
    cout << isIsomorphic(s3, t3) << endl;
    cout << isIsomorphic(s4, t4) << endl;
}
