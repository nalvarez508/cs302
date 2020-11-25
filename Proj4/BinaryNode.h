#ifndef BINARY_NODE_
#define BINARY_NODE_
#include <memory>

using namespace std;

template<class ItemType>
class BinaryNode
{
  private:
    ItemType item; // Data portion
    BinaryNode<ItemType> *leftChildPtr; // Pointer to left child
    BinaryNode<ItemType> *rightChildPtr; // Pointer to right child
  public:
    BinaryNode();
    BinaryNode(const ItemType& anItem);
    BinaryNode(const ItemType& anItem, BinaryNode<ItemType> *leftPtr, BinaryNode<ItemType> *rightPtr);
    void setItem(const ItemType& anItem);
    ItemType getItem() const;

    bool isLeaf() const;

    auto getLeftChildPtr() const;
    auto getRightChildPtr() const;
    
    void setLeftChildPtr(BinaryNode<ItemType> *leftPtr);
    void setRightChildPtr(BinaryNode<ItemType> *rightPtr);
}; // end BinaryNode

//Default
template<class ItemType>
BinaryNode<ItemType>::BinaryNode()
{
  this->leftChildPtr =  nullptr;
  this->rightChildPtr = nullptr;
  this->item = NULL;
}

//Parameter
template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem)
{
  this->leftChildPtr = nullptr;
  this->rightChildPtr = nullptr;
  this->item = anItem;
}

//Copy
template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &anItem, BinaryNode<ItemType> *leftPtr, BinaryNode<ItemType> *rightPtr)
{
  this->leftChildPtr = leftPtr;
  this->rightChildPtr = rightPtr;
  this->item = anItem;
}

//Set Item
template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &anItem)
{
  this->item = anItem;
}

//Get Item
template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
  return this->item;
}

//Is Leaf
template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
  //If both children do not exist, there are no children
  if (this->leftChildPtr == nullptr && this->rightChildPtr == nullptr)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//Get Left Child Pointer
template<class ItemType>
auto BinaryNode<ItemType>::getLeftChildPtr() const
{
  return this->leftChildPtr;
}

//Get Right Child Pointer
template<class ItemType>
auto BinaryNode<ItemType>::getRightChildPtr() const
{
  return this->rightChildPtr;
}

//Set Left Child Pointer
template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType> *leftPtr)
{
  this->leftChildPtr = leftPtr;
}

//Set Right Child Pointer
template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType> *rightPtr)
{
  this->rightChildPtr = rightPtr;
}
#endif