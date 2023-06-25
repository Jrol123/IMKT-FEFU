#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<string> topKFrequent(vector<string>& words, int k)
{
    map<string, int> frequency_map;
    for(const string& word : words)
    {
        frequency_map[word] ++;
    }

    vector<string> vector_answer;

    for(int count_dealt = 0; count_dealt < k; count_dealt ++)
    {
        unsigned int cur_max_count = 0;
        string cur_word = "";
        for (const auto &[word, count]: frequency_map)
        {
            if (cur_max_count < count || (cur_max_count == count && word < cur_word))
            {
                cur_word = word;
                cur_max_count = count;
            }
        }
        vector_answer.push_back(cur_word);
        frequency_map.erase(cur_word);
    }

    return vector_answer;
}

int main()
{
    vector<string> vc1 {"i","love","leetcode","i","love","coding"};
    const int k1 = 2;

    vector<string> vc2 {"the","day","is","sunny","the","the","the","sunny","is","is"};
    const int k2 = 4;

    vector<string> vca = topKFrequent(vc2, k2);
    for (const string& element : vca)
    {
        cout << element << endl;
    }
}
