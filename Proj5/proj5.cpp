//Code driver for Homework 5, Fall 2019, by Nick Alvarez
#include <iostream>
#include <algorithm> // for heap operations
#include <ctime> //random number seed

using namespace std;
const int MAX_AMT = 100;
const int MAX_INT = 200;

int generateRandom(const int min, const int max);

int main()
{ 
  //============ 1 ============
  // Initializing a vector
  vector<int> v;
  cout << endl << "Vector initialized." << endl << endl;
  int avgTotal = 0;
  int randomNum = 0;
  srand(time(NULL));

  cout << "Generating " << MAX_AMT << " random integers..." << endl;
  for (int i=0; i<MAX_AMT; i++)
  {
    randomNum = generateRandom(0, MAX_INT);
    avgTotal += randomNum;
    v.push_back(randomNum); //Vector is filled with 100 random ints
  }
  
  for (size_t i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl << endl;

  // Converting vector into a heap
  make_heap(v.begin(), v.end());
  cout << "Vector converted to heap." << endl;
  
  for (size_t i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl << endl;
  
  //============ 2 ============
  //Add new value that is mean of values
  avgTotal /= MAX_AMT;
  v.push_back(avgTotal);
  push_heap(v.begin(), v.end());
  cout << "Average value of elements is " << avgTotal << " and has been pushed into heap." << endl;
  
  for (size_t i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl << endl;

  //============ 3 ============
  //Delete maximum element of heap
  cout << "Maximum value of heap is " << v.front();
  pop_heap(v.begin(), v.end());
  v.pop_back();
  cout << " and has been popped from heap." << endl;
  
  for (size_t i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl << endl;

  //============ 4 ============
  //Sorting the heap
  cout << "Sorting the heap..." << endl << endl;
  sort_heap(v.begin(), v.end());
  cout << "Heap sorted." << endl;
  
  for (size_t i=0; i<v.size(); i++)
    cout << v[i] << " ";
  cout << endl << endl;
  
  /*// Displaying the maximum element of heap 
  // using front() (USED TO DELETE VALUE)
  cout << "The maximum element of heap is : ";
  cout << v1.front() << endl;
  
  // using push_back() to enter element
  // in vector
  v1.push_back(50);

  // using push_heap() to reorder elements
  push_heap(v1.begin(), v1.end());

  // Displaying the maximum element of heap
  // using front()
  cout << "The maximum element of heap after push is : ";
  cout << v1.front() << endl;

  // using pop_heap() to delete maximum element
  pop_heap(v1.begin(), v1.end());
  v1.pop_back();

  // Displaying the maximum element of heap
  // using front()
  cout << "The maximum element of heap after pop is : ";
  cout << v1.front() << endl;*/

  return 0; 
} 

int generateRandom(const int min, const int max)
{
  int btwn = max - min;
  return (rand() % btwn) + min;
}
