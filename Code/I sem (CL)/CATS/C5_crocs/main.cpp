#include <vector>
#include <fstream>
#include <string>
#include <iostream>
static const int maxLengthOfSide = 317;
using namespace std;

bool razm(int sumOfMoney, vector<int> & massOfCosts, int maxCountOfCases, int lastIndex, string & st)
{
  if(maxCountOfCases == 0 && sumOfMoney > 0)
  {
      return false;
  }
  if(sumOfMoney == 0)
  {
      return true;
  }
  for(int side = lastIndex + 1; side > 0; side--)
  {
      int costOfCase = massOfCosts[side - 1];
      if(costOfCase * maxCountOfCases >= sumOfMoney) // наибольший размер * макс кол-во >= кол-ву денег
      {
          if(costOfCase <= sumOfMoney)
          {
              if(razm(sumOfMoney - costOfCase, massOfCosts, maxCountOfCases - 1, side - 1, st))
              {
                  st = st + to_string(side) + " ";
                  return true;
              }
          }
      }
      else return false;
  }
  return false;

}

int main()
{

  vector<int> massOfCosts = {};
  int sumOfMoney, maxCountOfCases;
  string outString;

  ifstream inf ("input.txt");
  ofstream outf ("output.txt");

  inf >> sumOfMoney >> maxCountOfCases;
  inf.close();

  for(int side = 1; side < maxLengthOfSide; side++)
  {
      if(side * side > sumOfMoney)
      {
          break;
      }
      massOfCosts.push_back(side * side);
  }

  if(razm(sumOfMoney, massOfCosts, maxCountOfCases, massOfCosts.size() - 1, outString))
  {
      outf << "YES\n" << outString;
  }
  else
  {
      outf << "NO";
  }
  outf.close();

}