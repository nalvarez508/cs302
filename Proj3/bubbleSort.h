//Header file for BubbleSort class
//Nick Alvarez, CS302 F19

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

using namespace std;

class BubbleSort {
  public:
    BubbleSort(const int maxInput);
    ~BubbleSort();
    int getInput(const string &file);
    void sendOutput(const string &file);
    void sort();
    void print() const;
    long int getComparisons() const;
    long int getSwaps() const;
    
  private:
    int max; //ext
    int count;
    int *array;
    long int comparisons;
    long int swaps;
    void swap(int a, int b);
};

#endif
