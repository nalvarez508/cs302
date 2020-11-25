//Header file for MergeSort class
//Nick Alvarez, CS302 F19

#ifndef MERGESORT_H
#define MERGESORT_H

using namespace std;

class MergeSort {
  public:
    MergeSort(const int maxInput);
    ~MergeSort();
    int getInput(const string &file);
    void sendOutput(const string &file);
    void beginSort(); //Public sort call
    void print() const;
    int getComparisons() const;
    int getSwaps() const;
    
  private:
    int max; //ext
    int count;
    int *array;
    int comparisons;
    int swaps;
    void sort(int lo, int hi); //Overall sort function
    void merge(int lo, int mid, int hi);

};

#endif
