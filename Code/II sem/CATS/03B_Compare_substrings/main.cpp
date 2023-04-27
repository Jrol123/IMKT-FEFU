#include <iostream>
#include <cmath>
using namespace std;

const unsigned short multipl = 127;
long long calcCost(const long long massHash[], const long long massMul[], int beginIndex, int endIndex, int beginSecondStr)
{
    return (massHash[endIndex] - massHash[beginIndex - 1]) * massMul[beginSecondStr];
}

int main()
{
    string line;
    int countRequests;
    cin >> line >> countRequests;
    long long massHash [line.length()]; massHash[0] = int(line[0]);

    long long massMul[line.length()]; massMul[0] = 1;
    for (int index = 1; index < line.length(); ++index)
    {
        massMul[index] = massMul[index - 1] * multipl;
        massHash[index] = massHash[index - 1] + int(line[index]) * massMul[index];
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
            bool status = calcCost(massHash, massMul, begin1, end1, begin2) == calcCost(massHash, massMul, begin2, end2, begin1);
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
