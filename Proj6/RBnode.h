#ifndef RBNODE_
#define RBNODE_
#include <memory>

using namespace std;

template<class ItemType>
class RedBlackNode
{
  private:
    ItemType item; // Data portion
    RedBlackNode<ItemType> *leftChildPtr; // Pointer to left child
    RedBlackNode<ItemType> *rightChildPtr; // Pointer to right child
    bool red;
  public:
    RedBlackNode();
    RedBlackNode(const ItemType& anItem);
    //RedBlackNode(const ItemType& anItem, RedBlackNode<ItemType> *leftPtr, RedBlackNode<ItemType> *rightPtr, bool red);
    void setItem(const ItemType& anItem);
    ItemType getItem() const;

    RedBlackNode<ItemType>* getLeftChildPtr() const;
    RedBlackNode<ItemType>* getRightChildPtr() const;
    
    void setLeftChildPtr(RedBlackNode<ItemType> *leftPtr);
    void setRightChildPtr(RedBlackNode<ItemType> *rightPtr);

    bool getRed() const;
    void setRed(bool input);
    void colorReverse();
}; // end RedBlackNode

//Default
template<class ItemType>
RedBlackNode<ItemType>::RedBlackNode()
{
  this->leftChildPtr =  nullptr;
  this->rightChildPtr = nullptr;
  this->item = NULL;
  this->red = 0;
}

//Parameter
template<class ItemType>
RedBlackNode<ItemType>::RedBlackNode(const ItemType &anItem)
{
  this->leftChildPtr = nullptr;
  this->rightChildPtr = nullptr;
  this->item = anItem;
  this->red = 1;
}

//Copy
/*template<class ItemType>
RedBlackNode<ItemType>::RedBlackNode(const ItemType &anItem, RedBlackNode<ItemType> *leftPtr, RedBlackNode<ItemType> *rightPtr, bool red)
{
  this->leftChildPtr = leftPtr;
  this->rightChildPtr = rightPtr;
  this->item = anItem;
  this->red = red;
}*/

//Set Item
template<class ItemType>
void RedBlackNode<ItemType>::setItem(const ItemType &anItem)
{
  this->item = anItem;
}

//Get Item
template<class ItemType>
ItemType RedBlackNode<ItemType>::getItem() const
{
  return this->item;
}

//Get Left Child Pointer
template<class ItemType>
RedBlackNode<ItemType>* RedBlackNode<ItemType>::getLeftChildPtr() const
{
  return this->leftChildPtr;
}

//Get Right Child Pointer
template<class ItemType>
RedBlackNode<ItemType>* RedBlackNode<ItemType>::getRightChildPtr() const
{
  return this->rightChildPtr;
}

//Set Left Child Pointer
template<class ItemType>
void RedBlackNode<ItemType>::setLeftChildPtr(RedBlackNode<ItemType> *leftPtr)
{
  this->leftChildPtr = leftPtr;
}

//Set Right Child Pointer
template<class ItemType>
void RedBlackNode<ItemType>::setRightChildPtr(RedBlackNode<ItemType> *rightPtr)
{
  this->rightChildPtr = rightPtr;
}

//Get Red
template<class ItemType>
bool RedBlackNode<ItemType>::getRed() const
{
  return this->red;
}

//Set Red
template<class ItemType>
void RedBlackNode<ItemType>::setRed(bool input)
{
  this->red = input;
}

//Color Reverse
template<class ItemType>
void RedBlackNode<ItemType>::colorReverse()
{
  if (this->red)
  {
    this->red = 0;
    return;
  }

  this->red = 1;
}
#endif