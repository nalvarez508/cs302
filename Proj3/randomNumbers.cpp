//Simple program to make a text file with a user specified amount of random numbers
//Nick Alvarez, CS302 F19

#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

const int valBot = 0, valTop = 1000000;

//void generate(ofstream file, int amount);

int main()
{
  cout << "==============================" << endl;
  cout << "Nick's Random Number Generator" << endl;
  cout << "==============================" << endl << endl;

  int amount = 100;
  srand(time(NULL));

  cout << "Amount? ";
  cin >> amount;

  ofstream outFile;
  stringstream ss;
  ss << "random_" << amount << ".txt";
  string outfileName = ss.str();
  outFile.open(outfileName.c_str());

  clock_t start;
  double duration = 0;

  start = clock();
  for (int i=0; i<=amount; i++)
  {
    outFile << (rand() % valTop) << endl;
  }

  duration = (clock() - start)/(double) CLOCKS_PER_SEC;
  cout << "Printed " << amount << " integers to file in " << duration << "s" << endl;
  outFile.close();

  return 0;
}

/*void generate(ofstream file, int amount)
{
  for (int i=valBot; i<=valTop; i++)
  {
    file << (rand() % valTop) << endl;
  }

  cout << "Printed " << amount << "integers to file" << endl;
}*/