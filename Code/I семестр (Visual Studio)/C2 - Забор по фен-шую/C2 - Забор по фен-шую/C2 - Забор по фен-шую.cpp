#include <iostream>
#include <fstream>
using namespace std;
// Можно брать последний элемент изменения (10) и при необходимости менять его.
// Так 11 10 11 15 сначала просмотрится пара 11-10, потом 10-11, потом 10-15. из 11 в 16 перейти будет слишком сложно, поэтому поменяется 10.
// 
// Всего есть 3 переменных, iSCP, iPP и iP в порядке возрастания "новизны"
//
//Вывод в файл работает корректно
//
// Смотри комментарии в файле о проблемах

// Статус программы на данный момент: Всё должно работать, но оно не работает.

void switcher(int &iStateChangerPlank, int& iPreviousPlank, int& iPlank)
{
    if (iPlank > iPreviousPlank)
    {
        iStateChangerPlank += 1;
        //bStatePrevious = true;
    }
    else
    {
        iPreviousPlank += 1;
        //bStatePrevious = false;
    }
} // Попытка запихать 
int main()
{
    int iCountOfPlanks; // Количество досок
    int iStateChangerPlank; // Длина доски, изменившей последовательность (обычно 3-я в левую сторону от числа)
    int iPreviousPlank; // Длина предыдущей планки
    int iPlank; // Длина оперируемой планки
    bool bStatePrevious; // Статус последовательности в прошлом. false - опускается, true - поднимается
    bool bStateNow; // Статус последовательности на данный момент. false - опускается, true - поднимается
    bool bStateOfEqual = false;
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    inf >> iCountOfPlanks;
    cout << iCountOfPlanks << endl << endl;

    if (iCountOfPlanks > 1)
    {

        inf >> iStateChangerPlank >> iPreviousPlank;
        if (iStateChangerPlank == iPreviousPlank)
        {
            if (iCountOfPlanks > 2)
            {
                bStateOfEqual = true;
                inf >> iPlank;
                if (iPlank > iPreviousPlank)
                {
                    iStateChangerPlank += 1;
                    bStatePrevious = true;
                }
                else
                {
                    iPreviousPlank += 1;
                    bStatePrevious = false;
                }
                cout << iStateChangerPlank << " ";
                outf << iStateChangerPlank << " ";
                iStateChangerPlank = iPreviousPlank;
                iPreviousPlank = iPlank;
            }
            else
            {
                iStateChangerPlank += 1;
            }

        }
        else
        {
            bStatePrevious = (((iPreviousPlank - iStateChangerPlank) > 0) ? true : false);
        }

        for (int i = 2 + ((bStateOfEqual == false) ? 0 : 1); i < iCountOfPlanks; i++)
        {
            inf >> iPlank;

            bStateNow = (((iPlank - iPreviousPlank) > 0) ? true : false);
            if (iPlank == iPreviousPlank && ((i + 1) < iCountOfPlanks))
            {
                i += 1;
                iStateChangerPlank = iPreviousPlank;
                iPreviousPlank = iPlank;
                inf >> iPlank;
                switcher(iStateChangerPlank, iPreviousPlank, iPlank);
            }
            else if (iPlank == iPreviousPlank)
            {
                iPreviousPlank += 1;
            }
            else if (bStateNow == bStatePrevious)
            {
                if (bStateNow == true)
                {
                    int iRazn_PP_SCP = iPreviousPlank - iStateChangerPlank + 1; //Разница между PreviousPlank и StateChangerPlank + увеличение
                    int iRazn_P_PP = iPlank - iPreviousPlank + 1; //Разница между Plank и PreviousPlank + увеличение
                    // Мы можем увеличить или PP или SCP. Смотреть на разницу!
                    if (iRazn_P_PP < iRazn_PP_SCP)
                    {
                        iPreviousPlank += iRazn_P_PP;
                    } // Если дешевле увеличить PP
                    else
                    {
                        iStateChangerPlank += iRazn_PP_SCP;
                    } // Если дешевле увеличить SCP

                } // Если идёт на увеличение
                // Увеличение SCP приоритетное — т. к. тогда не западает || (11 10 11 12 11   ->   11 10 13 12 13) а могло быть (11 10 11 12 11   ->   11 12 11 12 11)
                //
                // PP увеличивается во всех остальных случаях

                else
                {
                    int iRazn_SCP_PP = iStateChangerPlank - iPreviousPlank + 1; //Разница между StateChangerPlank и PreviousPlank + увеличение
                    int iRazn_PP_P = iPreviousPlank - iPlank + 1; //Разница между PreviousPlank и Plank + увеличение
                    // Мы можем увеличить или P или PP.
                    if (iRazn_SCP_PP < iRazn_PP_P)
                    {
                        iPreviousPlank += iRazn_SCP_PP;
                    }
                    else
                    {
                        iPlank += iRazn_PP_P;
                    }

                } // Если идёт на уменьшение
                // Увеличение P приоритетное
                //
                // В остальных случаях увеличивается PP

            } //  Если несколько досок подряд не следуют пилообразной последовательности

            bStatePrevious = (((iPlank - iPreviousPlank) > 0) ? true : false);
            cout << iStateChangerPlank << " ";
            outf << iStateChangerPlank << " ";
            iStateChangerPlank = iPreviousPlank;
            iPreviousPlank = iPlank;
        }
        cout << iStateChangerPlank << " " << iPreviousPlank << endl;
        outf << iStateChangerPlank << " " << iPreviousPlank;
    }
    else
    {
        inf >> iPlank;
        cout << iPlank << endl;
        outf << iPlank;
    }

}