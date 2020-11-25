#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "MergeSort.h"

using namespace std;

MergeSort::MergeSort(const int maxInput) :
  max(maxInput),
  count(0),
  comparisons(0),
  swaps(0)
{
  array = new int[max];
}

MergeSort::~MergeSort()
{
  delete [] array;
}

int MergeSort::getInput(const string &file)
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

void MergeSort::sendOutput(const string &file)
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

void MergeSort::beginSort()
{
  sort(0, count);
}

void MergeSort::print() const
{
  for (int x=0; x<count; x++)
  {
    cout << array[x] << " ";
  }
  cout << endl;
}

int MergeSort::getComparisons() const
{
  return comparisons;
}
int MergeSort::getSwaps() const
{
  return swaps;
}

void MergeSort::sort(int lo, int hi)
{
  if (lo < hi)
  {
    int mid = lo+(hi-lo)/2;
    sort(lo, mid);
    sort(mid+1, hi);
    merge(lo, mid, hi);
  }
}

void MergeSort::merge(int lo, int mid, int hi)
{
  int x, y, z;
  int left = mid-lo+1;
  int right = hi-mid;
  int L[left], R[right];
  
  for (x=0; x<left; x++)
  {
    swaps++;
    L[x] = array[lo+x];
  }
  for (y=0; y<right; y++)
  {
    swaps++;
    R[y] = array[mid+1+y];
  }
  
  x=0;
  y=0;
  z=lo;
  
  while (x<left && y<right)
  {
    comparisons++;
    if (L[x] <= R[y])
    {
      swaps++;
      array[z] = L[x];
      x++;
    }
    else
    {
      swaps++;
      array[z] = R[y];
      y++;
    }
    z++;
  }
  while (x<left)
  {
    comparisons++;
    swaps++;
    array[z] = L[x];
    x++;
    z++;
  }
  while (y<right)
  {
    comparisons++;
    swaps++;
    array[z] = R[y];
    y++;
    z++;
  }
}
