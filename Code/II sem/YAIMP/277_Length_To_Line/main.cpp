#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

float lenght(int x, int y, int a, int b, int c)
{
  return (abs(a * x + b * y + c) / sqrt(pow(a, 2) + pow(b, 2)));
}

int main()
{
  int x, y, a, b, c;
  cin >> x >> y >> a >> b >> c;

  cout << fixed << lenght(x, y, a, b, c) << endl;
}