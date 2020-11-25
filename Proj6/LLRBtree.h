//Header and implementation file for the tree, Node is separate
//Class declaration somewhat pulled from Homework 6: BST and code package
//Nick Alvarez, HW6, Fall 2019
#ifndef LLRBTREE_
#define LLRBTREE_

#include <iostream>
#include <memory>
#include "RBnode.h"

using namespace std;

template<class ItemType>
class LeftLeaningRedBlackTree
{
  private:
    RedBlackNode<ItemType> *rootPtr;

  protected:
    //------------------------------------------------------------
    //    Protected Utility Methods Section:
    //    Recursive helper methods for the public methods.
    //------------------------------------------------------------

    int getHeightHelper(RedBlackNode<ItemType> *subTreePtr) const;
    int getNumberOfNodesHelper(RedBlackNode<ItemType> *subTreePtr) const;

    //Recursively adds new node to tree in left/right fashion to keep balance
    //auto balancedAdd(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNodePtr);

    // Places a given new node at its proper position in this binary search tree.
    //auto placeNode(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNode);

    // Places a given new node at its proper position in this red black tree.
    RedBlackNode<ItemType>* insertRec(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNode);

    // Removes the given target value from the tree while maintaining a red black tree.
    RedBlackNode<ItemType>* deleteRec(RedBlackNode<ItemType> *subTreePtr, const ItemType target);

    // Finds node with smallest value
    RedBlackNode<ItemType>* findMin(RedBlackNode<ItemType> *subTreePtr);

    // Deletes node with smallest value
    RedBlackNode<ItemType>* deleteMin(RedBlackNode<ItemType> *subTreePtr);

    // Rotate the subtree to the right.
    RedBlackNode<ItemType>* rotateRight(RedBlackNode<ItemType> *subTreePtr);

    // Rotate the subtree to the left.
    RedBlackNode<ItemType>* rotateLeft(RedBlackNode<ItemType> *subTreePtr);

    // Moves a red node to the left.
    RedBlackNode<ItemType>* moveRedLeft(RedBlackNode<ItemType> *subTreePtr);

    // Moves a red node to the right.
    RedBlackNode<ItemType>* moveRedRight(RedBlackNode<ItemType> *subTreePtr);
    
    // Removes the given target value from the tree while maintaining a binary search tree.
    //auto removeValue(RedBlackNode<ItemType> *subTreePtr, const ItemType target, bool& isSuccessful);
    
    // Removes a given node from a tree while maintaining a binary search tree.
    //auto removeNode(RedBlackNode<ItemType> *nodePtr);
    
    // Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
    // Sets inorderSuccessor to the value in this node.
    // Returns a pointer to the revised subtree.
    //auto removeLeftmostNode(RedBlackNode<ItemType> *subTreePtr, ItemType& inorderSuccessor);
    
    // Returns a pointer to the node containing the given value, or nullptr if not found.
    //auto findNode(RedBlackNode<ItemType> *subTreePtr, const ItemType& target) const;

    //Copies the tree rooted at treePtr and returns a pointer to the root of the tree
    auto copyTree(const RedBlackNode<ItemType> *oldTreeRootPtr) const;

    //Recursively deletes all nodes from the tree
    void destroyTree(RedBlackNode<ItemType> *subTreePtr);

    // Preserves balance of tree during deletion
    RedBlackNode<ItemType>* fixUp(RedBlackNode<ItemType> *subTreePtr);

    //Traversal Methods
    void preorder(RedBlackNode<ItemType> *subTreePtr) const;
    void inorder(RedBlackNode<ItemType> *subTreePtr) const;
    void postorder(RedBlackNode<ItemType> *subTreePtr) const;

    //Flips child colors below a certain node.
    void colorFlip(RedBlackNode<ItemType> *subTreePtr);

    //Checks if node is red or black.
    bool isRed(RedBlackNode<ItemType> *subTreePtr) const;

  public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------

    LeftLeaningRedBlackTree();
    LeftLeaningRedBlackTree(const ItemType& rootItem);
    LeftLeaningRedBlackTree(const LeftLeaningRedBlackTree<ItemType>& tree);
    virtual ~LeftLeaningRedBlackTree();

    //------------------------------------------------------------
    // Public Methods Section.
    //------------------------------------------------------------

    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;

    //ItemType getRootData() const throw(PrecondViolatedExcept);
    //void setRootData(const ItemType& newData);
    
    bool add(const ItemType& newEntry);
    void remove(const ItemType& target);
    //void clear();
    
    //ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
    //bool contains(const ItemType& anEntry) const;

    //------------------------------------------------------------
    // Public Traversals Section.
    //------------------------------------------------------------

    void preorderTraverse() const;
    void inorderTraverse() const;
    void postorderTraverse() const;
    
    //------------------------------------------------------------
    // Overloaded Operator Section.
    //------------------------------------------------------------

    /*LeftLeaningRedBlackTree<ItemType> &operator=(const LeftLeaningRedBlackTree<ItemType>& rightHandSide)
    {
      if (*this != rightHandSide)
      {
        this->rootPtr = rightHandSide->rootPtr;
        this->rootPtr.setLeftChildPtr(rightHandSide->getLeftChildPtr());
        this->rootPtr.setRightChildPtr(rightHandSide->getRightChildPtr());
      } //Faulty implementation but not necessary for driver
    }*/
}; // end LLRBTree

//Get Height Helper
template<class ItemType>
int LeftLeaningRedBlackTree<ItemType>::getHeightHelper(RedBlackNode<ItemType> *subTreePtr) const
{
  if (subTreePtr == nullptr)
  {
    return 0;
  }
  else
  {
    return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
  }
}

//Get Number of Nodes
template<class ItemType>
int LeftLeaningRedBlackTree<ItemType>::getNumberOfNodesHelper(RedBlackNode<ItemType> *subTreePtr) const
{
  int x = 1;
  if (subTreePtr == nullptr)
  {
    return 0;
  }
  else
  {
    x += getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
    x += getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
    return x;
  }
}

//Balanced add
/*template<class ItemType>
auto LeftLeaningRedBlackTree<ItemType>::balancedAdd(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNodePtr)
{
  if (subTreePtr == nullptr)
  {
    return newNodePtr;
  }
  else
  {
    RedBlackNode<ItemType> *leftPtr = subTreePtr->getLeftChildPtr();
    RedBlackNode<ItemType> *rightPtr = subTreePtr->getRightChildPtr();

    if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
    {
      rightPtr = balancedAdd(rightPtr, newNodePtr);
      subTreePtr->setRightChildPtr(rightPtr);
    }
    else
    {
      leftPtr = balancedAdd(leftPtr, newNodePtr);
      subTreePtr->setLeftChildPtr(leftPtr);
    }
    return subTreePtr;
  }
}*/

//Place node (DEPRECATED)
/*template<class ItemType>
auto LeftLeaningRedBlackTree<ItemType>::placeNode(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNodePtr)
{
  RedBlackNode<ItemType> *tempPtr = nullptr;
  if (subTreePtr == nullptr)
  {
    return newNodePtr;
  }
  else if (subTreePtr->getItem() > newNodePtr->getItem())
  {
    tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
    subTreePtr->setLeftChildPtr(tempPtr);
  }
  else
  {
    tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
    subTreePtr->setRightChildPtr(tempPtr);
  }
  return subTreePtr;
}*/

//Insert Recursively (new placeNode)
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::insertRec(RedBlackNode<ItemType> *subTreePtr, RedBlackNode<ItemType> *newNodePtr)
{
  RedBlackNode<ItemType> *tempPtr = nullptr;

  //Empty
  if (subTreePtr == nullptr)
  {
    return newNodePtr;
  }

  //Recurse left or right depending on data
  if (subTreePtr->getItem() > newNodePtr->getItem())
  {
    subTreePtr->setLeftChildPtr(insertRec(subTreePtr->getLeftChildPtr(), newNodePtr));
  }
  else
  {
    subTreePtr->setRightChildPtr(insertRec(subTreePtr->getRightChildPtr(), newNodePtr));
  }

  //Fix right leaning node
  if (isRed(subTreePtr->getRightChildPtr()) && !isRed(subTreePtr->getLeftChildPtr()))
  {
    subTreePtr = rotateLeft(subTreePtr);
  }

  //Fix two reds in a row
  if (isRed(subTreePtr->getLeftChildPtr()) && isRed(subTreePtr->getLeftChildPtr()->getLeftChildPtr()))
  {
    subTreePtr = rotateRight(subTreePtr);
  }

  //Color flips
  if (isRed(subTreePtr->getLeftChildPtr()) && isRed(subTreePtr->getRightChildPtr()))
  {
    colorFlip(subTreePtr);
  }

  //Return root of subtree
  return subTreePtr;
}

//Delete Recursively (new removeValue)
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::deleteRec(RedBlackNode<ItemType> *subTreePtr, const ItemType target)
{
  if (target < subTreePtr->getItem())
  {
    if (subTreePtr->getLeftChildPtr() != nullptr)
    {
      if (!isRed(subTreePtr->getLeftChildPtr()) && !isRed(subTreePtr->getLeftChildPtr()->getLeftChildPtr()))
      {
        subTreePtr = moveRedLeft(subTreePtr);
      }
      subTreePtr->setLeftChildPtr(deleteRec(subTreePtr->getLeftChildPtr(), target));
    }
  }
  else
  {
    if (isRed(subTreePtr->getLeftChildPtr()))
    {
      subTreePtr = rotateRight(subTreePtr);
    }

    if (target == subTreePtr->getItem() && subTreePtr->getRightChildPtr() == nullptr)
    {
      delete subTreePtr;
      return nullptr;
    }

    if (subTreePtr->getRightChildPtr() != nullptr)
    {
      if (!isRed(subTreePtr->getRightChildPtr()) && !isRed(subTreePtr->getRightChildPtr()->getLeftChildPtr()))
      {
        subTreePtr = moveRedRight(subTreePtr);
      }

      if (target == subTreePtr->getItem())
      {
        subTreePtr->setItem(findMin(subTreePtr->getRightChildPtr())->getItem());
        subTreePtr->setRightChildPtr(deleteMin(subTreePtr->getRightChildPtr()));
      }
      else
      {
        subTreePtr->setRightChildPtr(deleteRec(subTreePtr->getRightChildPtr(), target));
      }
    }
  }

  //Fix right leaning nodes
  return fixUp(subTreePtr);
}

//Find Min
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::findMin(RedBlackNode<ItemType> *subTreePtr)
{
  while (subTreePtr->getLeftChildPtr() != nullptr)
  {
    subTreePtr = subTreePtr->getLeftChildPtr();
  }

  return subTreePtr;
}

//Delete Min
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::deleteMin(RedBlackNode<ItemType> *subTreePtr)
{
  //No children, and no right child ever
  if (subTreePtr->getLeftChildPtr() == nullptr)
  {
    delete subTreePtr;
    return nullptr;
  }

  if (!isRed(subTreePtr->getLeftChildPtr()) && !isRed(subTreePtr->getLeftChildPtr()->getLeftChildPtr()))
  {
    subTreePtr = moveRedLeft(subTreePtr);
  }

  subTreePtr->setLeftChildPtr(deleteMin(subTreePtr->getLeftChildPtr()));

  return fixUp(subTreePtr);
}

//Rotate Right
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::rotateRight(RedBlackNode<ItemType> *subTreePtr)
{
  RedBlackNode<ItemType> *tempPtr = subTreePtr->getLeftChildPtr();
  subTreePtr->setLeftChildPtr(tempPtr->getRightChildPtr());
  tempPtr->setRightChildPtr(subTreePtr);
  tempPtr->setRed(subTreePtr->getRed());
  subTreePtr->setRed(1);

  return tempPtr;
}

//Rotate Left
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::rotateLeft(RedBlackNode<ItemType> *subTreePtr)
{
  RedBlackNode<ItemType> *tempPtr = subTreePtr->getRightChildPtr();
  subTreePtr->setRightChildPtr(tempPtr->getLeftChildPtr());
  tempPtr->setLeftChildPtr(subTreePtr);
  tempPtr->setRed(subTreePtr->getRed());
  subTreePtr->setRed(1);

  return tempPtr;
}

//Move Red Left
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::moveRedLeft(RedBlackNode<ItemType> *subTreePtr)
{
  colorFlip(subTreePtr);
  if ((subTreePtr->getRightChildPtr() != nullptr) && isRed(subTreePtr->getRightChildPtr()->getLeftChildPtr()))
  {
    subTreePtr->setRightChildPtr(rotateRight(subTreePtr->getRightChildPtr()));
    subTreePtr = rotateLeft(subTreePtr);

    colorFlip(subTreePtr);
  }

  return subTreePtr;
}

//Move Red Right
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::moveRedRight(RedBlackNode<ItemType> *subTreePtr)
{
  colorFlip(subTreePtr);
  if ((subTreePtr->getLeftChildPtr() != nullptr) && isRed(subTreePtr->getLeftChildPtr()->getLeftChildPtr()))
  {
    subTreePtr = rotateRight(subTreePtr);
    colorFlip(subTreePtr);
  }

  return subTreePtr;
}

//Remove Value (DEPRECATED)
/*template<class ItemType>
auto LeftLeaningRedBlackTree<ItemType>::removeValue(RedBlackNode<ItemType> *subTreePtr, const ItemType target, bool &isSuccessful)
{
  RedBlackNode<ItemType> *tempPtr = nullptr;
  if (subTreePtr == nullptr)
  {
    isSuccessful = 0;
  }
  else if (subTreePtr->getItem() == target)
  {
    subTreePtr = removeNode(subTreePtr);
    isSuccessful = 1;
  }
  else if (subTreePtr->getItem() > target)
  {
    tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
    subTreePtr->setLeftChildPtr(tempPtr);
  }
  else
  {
    tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
    subTreePtr->setRightChildPtr(tempPtr);
  }
  return subTreePtr;
}*/

//Remove Node (DEPRECATED)
/*template<class ItemType>
auto LeftLeaningRedBlackTree<ItemType>::removeNode(RedBlackNode<ItemType> *nodePtr)
{
  RedBlackNode<ItemType> *tempPtr = nullptr;
  ItemType newNodeValue = NULL;
  if (nodePtr->isLeaf())
  {
    nodePtr = nullptr;
    return nodePtr;
  }
  //N only has left child
  else if (nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() == nullptr)
  {
    return nodePtr->getLeftChildPtr();
  }
  //N has right child
  else if (nodePtr->getLeftChildPtr() == nullptr && nodePtr->getRightChildPtr() != nullptr)
  {
    return nodePtr->getRightChildPtr();
  }
  else
  {
    tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
    nodePtr->setRightChildPtr(tempPtr);
    nodePtr->setItem(newNodeValue);
    return nodePtr;
  }
}*/

//Remove Left Most Node (DEPRECATED)
/*template<class ItemType>
auto LeftLeaningRedBlackTree<ItemType>::removeLeftmostNode(RedBlackNode<ItemType> *nodePtr, ItemType &inorderSuccessor)
{
  RedBlackNode<ItemType> *tempPtr = nullptr;
  if (nodePtr->getLeftChildPtr() == nullptr)
  {
    inorderSuccessor = nodePtr->getItem();
    return removeNode(nodePtr);
  }
  else
  {
    tempPtr = removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor);
    nodePtr->setLeftChildPtr(tempPtr);
    return nodePtr;
  }
}*/

//Find node
/*template<class ItemType>
auto LeftLeaningRedBlackTree<ItemType>::findNode(RedBlackNode<ItemType> *subTreePtr, const ItemType &target) const
{
  if (subTreePtr == nullptr)
  {
    return nullptr;
  }
  else if (subTreePtr->getItem() == target)
  {
    return subTreePtr;
  }
  else if (subTreePtr->getItem() > target)
  {
    return findNode(subTreePtr->getLeftChildPtr(), target);
  }
  else
  {
    return findNode(subTreePtr->getRightChildPtr(), target);
  }
}*/

//Copy Tree
template<class ItemType>
auto LeftLeaningRedBlackTree<ItemType>::copyTree(const RedBlackNode<ItemType> *oldTreeRootPtr) const
{
  RedBlackNode<ItemType> *newTreePtr = nullptr;

  //Copy tree nodes during preorder traversal
  if (oldTreeRootPtr != nullptr)
  {
    //Copy the node
    newTreePtr = new RedBlackNode<ItemType>(oldTreeRootPtr->getItem(), nullptr, nullptr);
    newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
    newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
  }

  //Else tree is empty (newTreePtr is nullptr)
  return newTreePtr;
}

//Destroy Tree
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::destroyTree(RedBlackNode<ItemType> *subTreePtr)
{
  if (subTreePtr != nullptr)
  {
    destroyTree(subTreePtr->getLeftChildPtr());
    destroyTree(subTreePtr->getRightChildPtr());
    subTreePtr.reset(); //Decrement reference count to node. std::shared_ptr::reset()
  }
}

//Fix Up
template<class ItemType>
RedBlackNode<ItemType>* LeftLeaningRedBlackTree<ItemType>::fixUp(RedBlackNode<ItemType> *subTreePtr)
{
  if (isRed(subTreePtr->getRightChildPtr()))
  {
    subTreePtr = rotateLeft(subTreePtr);
  }

  if (isRed(subTreePtr->getLeftChildPtr()) && isRed(subTreePtr->getLeftChildPtr()->getLeftChildPtr()))
  {
    subTreePtr = rotateRight(subTreePtr);
  }

  if (isRed(subTreePtr->getLeftChildPtr()) && isRed(subTreePtr->getRightChildPtr()))
  {
    colorFlip(subTreePtr);
  }

  return subTreePtr;
}

//Preorder helper
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::preorder(RedBlackNode<ItemType> *subTreePtr) const
{
  if(subTreePtr != nullptr)
  {
    cout << subTreePtr->getItem() << "[" << (subTreePtr->getRed() ? "red" : "black") << "], ";
    preorder(subTreePtr->getLeftChildPtr());
    preorder(subTreePtr->getRightChildPtr());
  }
}

//Inorder helper
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::inorder(RedBlackNode<ItemType> *subTreePtr) const
{
  if(subTreePtr != nullptr)
  {
    inorder(subTreePtr->getLeftChildPtr());
    cout << subTreePtr->getItem() << "[" << (subTreePtr->getRed() ? "red" : "black") << "], ";
    inorder(subTreePtr->getRightChildPtr());
  }
}

//Postorder helper
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::postorder(RedBlackNode<ItemType> *subTreePtr) const
{
  if(subTreePtr != nullptr)
  {
    postorder(subTreePtr->getLeftChildPtr());
    postorder(subTreePtr->getRightChildPtr());
    cout << subTreePtr->getItem() << "[" << (subTreePtr->getRed() ? "red" : "black") << "], ";
  }
}

//Color Flip
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::colorFlip(RedBlackNode<ItemType> *subTreePtr)
{
  subTreePtr->colorReverse();
  if (subTreePtr->getLeftChildPtr() != nullptr)
  {
    subTreePtr->getLeftChildPtr()->colorReverse();
  }
  if (subTreePtr->getRightChildPtr() != nullptr)
  {
    subTreePtr->getRightChildPtr()->colorReverse();
  }
}

//Is Red
template<class ItemType>
bool LeftLeaningRedBlackTree<ItemType>::isRed(RedBlackNode<ItemType> *subTreePtr) const
{
  if (subTreePtr != nullptr)
  {
    return subTreePtr->getRed();
  }

  return 0; //Black for nullptr
}

//Default
template<class ItemType>
LeftLeaningRedBlackTree<ItemType>::LeftLeaningRedBlackTree() : rootPtr(nullptr)
{
}

//Parameterized
template<class ItemType>
LeftLeaningRedBlackTree<ItemType>::LeftLeaningRedBlackTree(const ItemType &rootItem)
{
  this->rootPtr = new RedBlackNode<ItemType>(rootItem);
}

//Copy
template<class ItemType>
LeftLeaningRedBlackTree<ItemType>::LeftLeaningRedBlackTree(const LeftLeaningRedBlackTree<ItemType> &tree)
{
  this->rootPtr = copyTree(tree.rootPtr);
}

//Destructor
template<class ItemType>
LeftLeaningRedBlackTree<ItemType>::~LeftLeaningRedBlackTree()
{
  this->rootPtr = nullptr;
  delete this->rootPtr;
}

//Is Empty
template<class ItemType>
bool LeftLeaningRedBlackTree<ItemType>::isEmpty() const
{
  if (this->rootPtr == nullptr)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//Get Height
template<class ItemType>
int LeftLeaningRedBlackTree<ItemType>::getHeight() const
{
  return getHeightHelper(this->rootPtr);
}

//Get Number of Nodes
template<class ItemType>
int LeftLeaningRedBlackTree<ItemType>::getNumberOfNodes() const
{
  return getNumberOfNodesHelper(this->rootPtr); 
}

//Get Root Data
/*template<class ItemType>
ItemType LeftLeaningRedBlackTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
  if (this->rootPtr == nullptr)
  {
    throw "Root does not exist!";
  }
  return rootPtr->getItem();
}*/

//Set Root Data
/*template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::setRootData(const ItemType &newData)
{
  rootPtr->setItem(newData);
}*/

//Add
template<class ItemType>
bool LeftLeaningRedBlackTree<ItemType>::add(const ItemType &newData)
{
  RedBlackNode<ItemType> *newNodePtr = new RedBlackNode<ItemType>(newData);
  this->rootPtr = insertRec(rootPtr, newNodePtr);
  rootPtr->setRed(0);
  return 1;
}

//Remove
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::remove(const ItemType &target)
{
  if (rootPtr != nullptr)
  {
    this->rootPtr = deleteRec(this->rootPtr, target);
    if (rootPtr != nullptr)
    {
      rootPtr->setRed(0);
    }
  }
}

//Clear (faulty, no target)
/*template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::clear()
{
  if(this->rootPtr != nullptr)
  {
    deleteRec(rootPtr->getLeftChildPtr());
    deleteRec(rootPtr->getRightChildPtr());

    rootPtr->setLeftChildPtr(nullptr);
    rootPtr->setRightChildPtr(nullptr);

    delete this->rootPtr;
    this->rootPtr = nullptr;
  }
  this->rootPtr = nullptr;
}*/

//Get Entry
/*template<class ItemType>
ItemType LeftLeaningRedBlackTree<ItemType>::getEntry(const ItemType &anEntry) const throw(NotFoundException)
{
  auto result = findNode(this->rootPtr, anEntry);
  if (result == nullptr)
  {
    throw "Null Pointer encountered";
  }
  else
  {
    return *result;
  }
}*/

//Contains
/*template<class ItemType>
bool LeftLeaningRedBlackTree<ItemType>::contains(const ItemType &anEntry) const
{
  bool isSuccessful = 0;
  auto result = findNode(this->rootPtr, anEntry);
  if (result == nullptr)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}*/

//Preorder traverse
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::preorderTraverse() const
{
  preorder(this->rootPtr);
}


//Inorder traverse
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::inorderTraverse() const
{
  inorder(this->rootPtr);
}

//Postorder traverse
template<class ItemType>
void LeftLeaningRedBlackTree<ItemType>::postorderTraverse() const
{
  postorder(this->rootPtr);
}

/*//Overloaded assignment (incp)
template<class ItemType>
LeftLeaningRedBlackTree<ItemType>::&operator=(const LeftLeaningRedBlackTree<ItemType> &rightHandSide)
{
  if (*this != rightHandSide)
  {
    this->rootPtr = rightHandSide->rootPtr;
    this->rootPtr.setLeftChildPtr(rightHandSide->getLeftChildPtr());
    this->rootPtr.setRightChildPtr(rightHandSide->getRightChildPtr());
  } //Faulty implementation but not necessary for driver
}*/

#endif