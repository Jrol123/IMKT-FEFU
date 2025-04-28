#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int iHours, iMinutes;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iHours >> iMinutes;
    cout << iHours << " " << iMinutes << endl << endl;
    int iLastHour = 24, iLastMinutes = 0;
    iLastHour -= iHours;
    if (iMinutes != 0)
    {
        iLastHour -= 1;
        iLastMinutes = 60 - iMinutes;
    }
    cout << iLastHour << " " << iLastMinutes << endl;
    outf << iLastHour << " " << iLastMinutes;
}
