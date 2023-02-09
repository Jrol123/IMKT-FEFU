#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    int iCountOfStrPerPage, iIndexOfStr;
    ifstream inf("a.in");
    ofstream outf("a.out");
    inf >> iCountOfStrPerPage >> iIndexOfStr;
    cout << iCountOfStrPerPage << " " << iIndexOfStr << endl << endl;

    int iIndexOfPage = ceil((double)iIndexOfStr / iCountOfStrPerPage);
    int iIndexOfStrOnPage = iCountOfStrPerPage + (iIndexOfStr - (iIndexOfPage * iCountOfStrPerPage));

    outf << iIndexOfPage << " " << iIndexOfStrOnPage;
    cout << iIndexOfPage << " " << iIndexOfStrOnPage << endl;
}
