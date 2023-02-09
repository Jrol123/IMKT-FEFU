#include <iostream>
#include <limits>
#include <climits>
#include <iomanip>
using namespace std;

int main()
{
	int iNum1 = 1;
	setlocale(LC_ALL, "Russian");
	cout << setw(6) << "Тип" << setw(10) << "Байт" << setw(30) << "Min" << setw(30) << "Max" << endl << endl; //13 пробелов

	cout << setw(6) << "bool" << setw(10) << sizeof(bool) << setw(30) << numeric_limits<bool>::min() << setw(30) << numeric_limits<bool>::max() << endl << endl;
	cout << setw(6) << "char" << setw(10) << sizeof(char) << setw(30) << CHAR_MIN << setw(30) << CHAR_MAX << endl;
	cout << setw(6) << "uChar" << setw(10) << sizeof(unsigned char) << setw(30) << 0 << setw(30) << UCHAR_MAX << endl << endl;

	cout << setw(6) << "string" << setw(10) << sizeof(string) << setw(30) << numeric_limits<string>::min() << setw(30) << numeric_limits<string>::max() << endl << endl;

	cout << setw(6) << "int" << setw(10) << sizeof(int) << setw(30) << INT_MIN << setw(30) << INT_MAX << endl;
	cout << setw(6) << "uInt" << setw(10) << sizeof(unsigned int) << setw(30) << 0 << setw(30) << UINT_MAX << endl;
	cout << setw(6) << "uSInt" << setw(10) << sizeof(unsigned short int) << setw(30) << 0 << setw(30) << numeric_limits<unsigned short int>::max() << endl;
	cout << setw(6) << "sInt" << setw(10) << sizeof(short int) << setw(30) << numeric_limits<short int>::min() << setw(30) << numeric_limits<short int>::max() << endl;
	cout << setw(6) << "Lint" << setw(10) << sizeof(long int) << setw(30) << numeric_limits<long int>::min() << setw(30) << numeric_limits<long int>::max() << endl;
	cout << setw(6) << "LLint" << setw(10) << sizeof(long long int) << setw(30) << numeric_limits<long long int>::min() << setw(30) << numeric_limits<long long int>::max() << endl;
	cout << setw(6) << "uLInt" << setw(10) << sizeof(unsigned long int) << setw(30) << 0 << setw(30) << numeric_limits<unsigned long int>::max() << endl;
	cout << setw(6) << "uLLInt" << setw(10) << sizeof(unsigned long long int) << setw(30) << 0 << setw(30) << numeric_limits<unsigned long long int>::max() << endl << endl;

	cout << setw(6) << "float" << setw(10) << sizeof(float) << setw(30) << numeric_limits<float>::min() << setw(30) << numeric_limits<float>::max() << endl;
	cout << setw(6) << "lFloat" << setw(10) << sizeof(long float) << setw(30) << numeric_limits<long float>::min() << setw(30) << numeric_limits<long float>::max() << endl << endl;

	cout << setw(6) << "double" << setw(10) << sizeof(double) << setw(30) << numeric_limits<double>::min() << setw(30) << numeric_limits<double>::max() << endl << endl;

}