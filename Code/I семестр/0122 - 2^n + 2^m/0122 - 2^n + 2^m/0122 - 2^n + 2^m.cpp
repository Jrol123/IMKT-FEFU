#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    cout << ((1 << n) | (1 << m)); // по условию, n != m
}