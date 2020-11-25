//Test driver for two sorting classes
//Nick Alvarez, CS302 F19

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "bubbleSort.h"
#include "mergeSort.h"

using namespace std;

int main()
{
  int sizeInput;
  char sortInput;
  string fileName;
  ifstream inFile;
  ofstream outFile;

  cout << "Nick's Sort Comparison Test 1.0" << endl << endl;
  cout << "Size of array to test [1000, 10000, 100000]: ";
  cin >> sizeInput;
  BubbleSort bSort(sizeInput);
  MergeSort mSort(sizeInput);

  switch(sizeInput)
  {
    case 100:
    {
      fileName = "random_100.txt";
      break;
    }
    case 1000:
    {
      cout << "Sorted? [y/n]: ";
      cin >> sortInput;
      if (sortInput == 'y')
      {
        fileName = "sorted_random_1000.txt";
      }
      else
      {
        fileName = "random_1000.txt";
      }
      break;
    }
    case 10000:
    {
      cout << "Sorted? [y/n]: ";
      cin >> sortInput;
      if (sortInput == 'y')
      {
        fileName = "sorted_random_10000.txt";
      }
      else
      {
        fileName = "random_10000.txt";
      }
      break;
    }
    case 100000:
    {
      cout << "Sorted? [y/n]: ";
      cin >> sortInput;
      if (sortInput == 'y')
      {
        fileName = "sorted_random_100000.txt";
      }
      else
      {
        fileName = "random_100000.txt";
      }
      break;
    }
    default:
      cout << "Invalid input parameters" << endl;
  }

  bSort.getInput(fileName.c_str());
  mSort.getInput(fileName.c_str());

  cout << "Testing bubble sort with " << sizeInput << ((sortInput == 'y') ? " sorted" : " unsorted") << " items..." << endl;
  clock_t bTime;
  double bDuration = 0;
  bTime = clock();
  bSort.sort();
  bDuration = (clock() - bTime)/(double) CLOCKS_PER_SEC;
  bSort.sendOutput(fileName.c_str());

  cout << "Testing merge sort with " << sizeInput << ((sortInput == 'y') ? " sorted" : " unsorted") << " items..." << endl;
  clock_t mTime;
  double mDuration = 0;
  mTime = clock();
  mSort.beginSort();
  mDuration = (clock() - mTime)/(double) CLOCKS_PER_SEC;

  cout << endl;
  cout << fixed << "|             | Bubble Sort \t\t| Merge Sort \t\t|" << endl
       << "|    Times    | " << bDuration << "s\t\t| " << mDuration << "s\t\t|" << endl
       << "| Comparisons | " << bSort.getComparisons() << ((sizeInput <= 1000) ? "\t" : "") << "\t\t| " << mSort.getComparisons() << ((sizeInput <= 1000) ? "\t" : "") << "\t\t|" << endl
       << "|    Swaps    | " << bSort.getSwaps() << ((sizeInput <= 1000) ? "\t" : "") << ((sortInput == 'y' && sizeInput > 1000) ? "\t" : "") << "\t\t| " << mSort.getSwaps() << ((sizeInput <= 1000) ? "\t" : "") << "\t\t|" << endl;
  
  return 0;
}