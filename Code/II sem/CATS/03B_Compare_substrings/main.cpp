#include <iostream>
#include <cmath>
using namespace std;

const unsigned short multipl = 1;

int calcCost(long long massCosts[], int beginIndex, int endIndex)
{
    return (massCosts[endIndex] - massCosts[beginIndex - 1]) / pow(multipl, beginIndex);
}

int main()
{
    string line;
    int countRequests;
    cin >> line >> countRequests;
    long long massCosts [line.length()]; massCosts[0] = int(line[0]);

    for (int index = 1; index < line.length(); ++index)
    {
        massCosts[index] = massCosts[index - 1] + int(line[index]) * pow(multipl, index);
    }
    for (int index = 0; index < countRequests; ++index)
    {
        int begin1, end1, begin2, end2;
        cin >> begin1 >> end1 >> begin2 >> end2;
        begin1 --; end1--; begin2--; end2--;

        if (begin1 == begin2 & end1 == end2)
        {
            cout << "Yes" << endl;
        }
        else if(end1 - begin1 == end2 - begin2)
        {
            bool status = calcCost(massCosts, begin1, end1) == calcCost(massCosts, begin2, end2);
            switch (status)
            {
                case true:
                    cout << "Yes";
                    break;
                case false:
                    cout << "No";
                    break;
            }
            cout << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}
/*
trololo
3
1 7 1 7
3 5 5 7
1 1 1 5

 */
