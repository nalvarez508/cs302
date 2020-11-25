//--------------------------------------------------------------------
//
//  StackArray.h
// 
//  Class declaration for the array implementation of the Stack ADT
//
//--------------------------------------------------------------------

#ifndef STACKARRAY_H
#define STACKARRAY_H

#include <stdexcept>
#include <iostream>

using namespace std;

#include "Stack.h"

template <typename DataType>
class StackLinked : public Stack<DataType> {

  public:

    StackLinked(int maxNumber = Stack<DataType>::MAX_STACK_SIZE);
    StackLinked(const StackLinked& other);
    StackLinked& operator=(const StackLinked& other);
    ~StackLinked();

    void push(const DataType& newDataItem) throw (logic_error);
    DataType pop() throw (logic_error);

    void clear();

    bool isEmpty() const;
    bool isFull() const;

    void showStructure() const;

  private:

    class StackNode {
      public:
	      StackNode(const DataType& nodeData, StackNode* nextPtr);

      	DataType dataItem;
	      StackNode* next;
    };

    StackNode* top;
};

//Default constructor
template<class DataType>
StackLinked<DataType>::StackLinked(int maxNumber) :
  top(nullptr)
{

}

//Copy constructor
template<class DataType>
StackLinked<DataType>::StackLinked(const StackLinked& other)
{
  StackNode *curr = top;
  StackNode *newCurr = other.top;
  while (newCurr != nullptr)
  {
    curr = new StackNode(newCurr->dataItem, newCurr->next);
    //First element?
    if (top == nullptr)
    {
      top = curr;
    }
    curr = curr->next;
    newCurr = newCurr->next;
  }
}

//Assignment operator overload
template<class DataType>
StackLinked<DataType>& StackLinked<DataType>::operator=(const StackLinked& other)
{
  if (this != other)
  {
    clear();
    top = other->top;
  }
  return *this;
}

//Destructor
template<class DataType>
StackLinked<DataType>::~StackLinked()
{
  clear();
}

//Puts item at top of list using StackNode
template<class DataType>
void StackLinked<DataType>::push(const DataType& newDataItem) throw (logic_error)
{
  //No error to throw as this will always place a new item on top, items or not
  top = new StackNode(newDataItem, top);
}

//Reads topmost item from list
template<class DataType>
DataType StackLinked<DataType>::pop() throw (logic_error)
{
  if (isEmpty())
  {
    throw logic_error("Stack is empty\n");
  }
  DataType topStack = top->dataItem;
  top = top->next;
  return topStack;
}

//Deletes entire list
template<class DataType>
void StackLinked<DataType>::clear()
{
  StackNode *curr = top;
  StackNode *previous = nullptr;

  while (curr!=nullptr)
  {
    previous = curr;
    curr = curr->next;
    delete previous;
  }
}

//Checks if list is empty
template<class DataType>
bool StackLinked<DataType>::isEmpty() const
{
  return (top == nullptr) ? 1 : 0;
}

//Checks if list is full. This should always return false.
template<class DataType>
bool StackLinked<DataType>::isFull() const
{
  return 0;
}

//Prints list
template<class DataType>
void StackLinked<DataType>::showStructure() const
{
  if (isEmpty())
  {
    cout << "Stack is empty\n";
  }
  else
  {
    StackNode *curr = top;
    while (curr != nullptr)
    {
      cout << curr->dataItem << "\n";
      curr = curr->next;
    }
  }
}

//Node class, creates new item with data of 
template<class DataType>
StackLinked<DataType>::StackNode(const DataType& nodeData, StackNode* nextPtr) :
  dataItem(nodeData), next(nodePtr)
{

}

#endif		//#ifndef STACKARRAY_H

