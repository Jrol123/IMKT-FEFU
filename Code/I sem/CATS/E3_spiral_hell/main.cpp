#include <iostream>
#include <fstream>
using namespace std;

int main(){

  int rank, N, index, j, numOfLine, ch = 0, sh_kr = 0, countOfRightElem = 0, k = 0;

  ifstream inf("input.txt");
  ofstream outf("output.txt");

  inf >> rank >> numOfLine;

  // 2 - 1
  // 3 - 2
  // 4 - 2
  // 5 - 3
  // 6 - 3
  if (numOfLine > rank / 2 + rank % 2)
  {
      countOfRightElem = rank - numOfLine + 1;
    //Кол-во элементов, которые считаются через круг слева\справа
  } // Если дальше середины
  else
  {
      countOfRightElem = numOfLine - 1; // Кол-во элементов, дальше середины
  } // Если ближе середины

  int massOfCycles[countOfRightElem]; // Массив "циклов до оборота", всех элементов, после центра, считающихся через круг.
  // Считается справа-налево.

  for(index = 0; index < rank; index++)
  {
    if(numOfLine == 1)
    {
      for(j = 0; j < rank; j++)
      {
        outf << rank * rank - j << " ";
      }
      break;
    } // Вывод в тупую верхней строчки

    if(index < countOfRightElem)
    {
      sh_kr = sh_kr + ((4 * (rank - 1 - index * 2) - 1)); // Шаги по полному кругу
      // До последнего элемента в круге включительно
      // 15 | 7
      ch = rank * rank - sh_kr + (numOfLine - 2 * (index + 1)); // Элемент на вывод (слева-направо
//      krugi++;

      massOfCycles[index] = sh_kr + index - (rank - 2 * (index + 1)) - (rank - 1 - 2 * index) - ((rank - numOfLine) - index);
      // 9 - 4 = 5

      outf << ch << " ";
    }


    if ((index >= countOfRightElem) && (index < countOfRightElem + (rank - 2 * countOfRightElem)) && (numOfLine <= rank / 2 + rank % 2))
    {
      //Элементы, которые считаются вычитанием единицы, т.к. идут слева направо
      ch--;
      outf << ch << " ";
    }
    else if ((index >= countOfRightElem) && (index < countOfRightElem + (rank - 2 * countOfRightElem)) && (numOfLine > rank / 2 + rank % 2))
    {
      //элементы, которые считаются прибавлением единицы
      ch++;
      outf << ch << " ";
    }
    // Блок, посвящённый "линии" в центре, где возможно найти нужные элементы путём прибавления / вычитания 1-цы

    // Возможно, стоит сделать случай с последней строчкой (rank == numOfLine)

    if (index >= countOfRightElem + (rank - 2 * countOfRightElem))
    {

      for (j = countOfRightElem - 1; j >= 0; j--)
      {
        outf << rank * rank - massOfCycles[j] << " ";
      }
      break;
    }
  }

  //4*(rank-1-index*2)-1 index-тый круг
  //(numOfLine-1)-index кол-во шагов, чтоб вернуться в нужную строку
  //(stroki) кол-во элементов, которые считаются через круг слева\справа
  //rank-2*(stroki) кол-во элементов которые считаются вычитанием единицы

}
