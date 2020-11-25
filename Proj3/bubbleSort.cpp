#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "bubbleSort.h"

using namespace std;

BubbleSort::BubbleSort(const int maxInput) :
  max(maxInput),
  count(0),
  comparisons(0),
  swaps(0)
{
  array = new int[max];
}

BubbleSort::~BubbleSort()
{
  delete [] array;
}

int BubbleSort::getInput(const string &file)
{
  ifstream infile;
  infile.open(file.c_str());

  int x=0;
  while (!infile.eof() && x<max)
  {
    infile >> array[x];
    count++;
    x++;
  }
  infile.close();
  return x;
}

void BubbleSort::sendOutput(const string &file)
{
  ofstream outfile;
  stringstream ss;
  ss << "sorted_" << file;
  string outName = ss.str();
  outfile.open(outName.c_str());

  for (int x=0; x<count; x++)
  {
    outfile << array[x] << endl;
  }
}
void BubbleSort::sort()
{
  comparisons=0;
  swaps=0;
  for (int i = 0; i < count-1; i++)
  {
    for (int j = 0; j < count-1 - i; j++)
    {
      comparisons++;
      if (array[j] > array[j + 1])
      {
        swap(j, j+1);
        swaps++;
      }
    }
  }
}

void BubbleSort::print() const
{
  for (int x=0; x<count; x++)
  {
    cout << array[x] << " ";
  }
  cout << endl;
}

void BubbleSort::swap(int a, int b)
{
  int temp = 0;
  temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}

int BubbleSort::getComparisons() const
{
  return comparisons;
}
int BubbleSort::getSwaps() const
{
  return swaps;
}
