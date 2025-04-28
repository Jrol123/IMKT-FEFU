#include <iostream>
using namespace std;
int main()
{
    int iDayOfBirth, iMonthOfBirth, iTDay, iTMonth, iTYear;
    cin >> iDayOfBirth >> iMonthOfBirth >> iTDay >> iTMonth >> iTYear;

    int a1 = (14 - iTMonth) / 12;
    int y1 = iTYear + 4800 - a1;
    int m1 = iTMonth + 12 * a1 - 3;

    int iJDN_Date_Now = iTDay + ((153 * m1 + 2) / 5) + 365 * y1 + (y1 / 4) - (y1 / 100) + (y1 / 400) - 32045; // Дата текущего дня по ЮД

    bool bStateOfYear = (((iTYear % 100 != 0) && (iTYear % 4 == 0)) || (iTYear % 400 == 0)); // Високосный ли год

    if (((iDayOfBirth == 29) && (bStateOfYear == true) && (iMonthOfBirth == 2) && (iMonthOfBirth < iTMonth)) || ((bStateOfYear == false) && (iDayOfBirth == 29) && (iMonthOfBirth == 2)))
    {
        do
        {
            iTYear += 1;
        } while (!(((iTYear % 100 != 0) && (iTYear % 4 == 0)) || (iTYear % 400 == 0)));
    } // если текущий год високосный и ДР 29.02 и ДР уже было в этом году или если текущий год НЕ високосный и ДР 29.02
    else if ((iDayOfBirth < iTDay) && (iMonthOfBirth <= iTMonth))
    {
        //cout << "s2" << endl;
        iTYear += 1;
    } // если ДР в этом году уже было и ДР не 29.02

    int a2 = (14 - iMonthOfBirth) / 12; // есть ли январь или февраль
    int y2 = iTYear + 4800 - a2;
    int m2 = iMonthOfBirth + 12 * a2 - 3;

    int iJDN_Date_Birth = iDayOfBirth + ((153 * m2 + 2) / 5) + 365 * y2 + (y2 / 4) - (y2 / 100) + (y2 / 400) - 32045; // Дата дня рождения по ЮД

    cout << iJDN_Date_Birth - iJDN_Date_Now;
}