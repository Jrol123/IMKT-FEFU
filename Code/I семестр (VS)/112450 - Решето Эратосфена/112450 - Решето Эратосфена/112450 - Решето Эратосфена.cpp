#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int iMainNum; // Главное число
    vector <int> iMainMass;
    cin >> iMainNum;

    for (int i = 2; i <= iMainNum; i++)
    {
        iMainMass.push_back(i);
    }

    vector <int> iSubMass = iMainMass;

    for (int i = 0; i <= iMainNum - 2; i++)
    {
        int iNum = iMainMass[i];
        /*for (int iSubNum : iSubMass)
        {
            if (iSubNum % iNum == 0 && iSubNum != iNum)
            {
                auto *pointer = &iSubNum;
                iSubMass.erase(pointer);
            }
            else
            {
                iCount += 1;
            }
        } Не прокатила идея с удалением элементов*/
        
        if (iSubMass[i] != 0)
        {
            cout << iSubMass[i] << " ";
            for (int iIndex = i + 1; iIndex <= iMainNum - 2; iIndex++)
            {
                int iSubNum = iMainMass[iIndex];
                if (iSubNum % iNum == 0)
                {
                    iSubMass[iIndex] = 0;
                }
            }
        }
    }
    //for (int i : iSubMass)
    //{
    //    if (i != 0)
    //    {
    //        cout << i << " ";
    //    }
    //}
}