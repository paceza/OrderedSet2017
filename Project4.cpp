/********************************************
 * Project : Project4
 * File : Project4.cpp
 * Author: Zack Pace
 * Description: Sample application file to use OrderedSet and WordData classes together
 *******************************************/

#include <iostream>
#include <fstream>
#include "OrderedSet.hpp"
#include "WordData.h"

using namespace std;

int WordDataTest (string file);

int main (int argc, char * argv [])
{
  WordDataTest("words.txt");
  return 0;
}

int WordDataTest (string file)
{
  cout << "Testing OrderedSet with WordData:\n\n";
  ifstream input (file.c_str());
  WordData oneword;
  OrderedSet<WordData> WD;
  while (input >> oneword)
    WD.Insert (oneword);
  input.close();
  OrderedSet<WordData>::Iterator itr;
  cout << "From first to last:\n";
  for (itr = WD.begin(); itr != WD.end(); itr++)
    cout << '\t' << *itr << endl;
  cout << "From last to first:\n";
  for (itr = WD.rbegin(); itr != WD.rend(); --itr)
    cout << '\t' << *itr << endl;
  cout << "End of OrderedSet with WordData test\n\n";
  return 0;
  
}
