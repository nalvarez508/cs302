//varName : variable type
/** Link-based implementation of the ADT binary search tree.
@file BinarySearchTree.h */
#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"
#include <memory>
#include <iostream>

using namespace std;

template<class ItemType>
class BinarySearchTree
{
  private:
    BinaryNode<ItemType> *rootPtr;

  protected:
    //------------------------------------------------------------
    //    Protected Utility Methods Section:
    //    Recursive helper methods for the public methods.
    //------------------------------------------------------------

    int getHeightHelper(BinaryNode<ItemType> *subTreePtr) const;
    int getNumberOfNodesHelper(BinaryNode<ItemType> *subTreePtr) const;

    //Recursively adds new node to tree in left/right fashion to keep balance
    auto balancedAdd(BinaryNode<ItemType> *subTreePtr, BinaryNode<ItemType> *newNodePtr);

    // Places a given new node at its proper position in this binary search tree.
    auto placeNode(BinaryNode<ItemType> *subTreePtr, BinaryNode<ItemType> *newNode);
    
    // Removes the given target value from the tree while maintaining a binary search tree.
    auto removeValue(BinaryNode<ItemType> *subTreePtr, const ItemType target, bool& isSuccessful);
    
    // Removes a given node from a tree while maintaining a binary search tree.
    auto removeNode(BinaryNode<ItemType> *nodePtr);
    
    // Removes the leftmost node in the left subtree of the node pointed to by nodePtr.
    // Sets inorderSuccessor to the value in this node.
    // Returns a pointer to the revised subtree.
    auto removeLeftmostNode(BinaryNode<ItemType> *subTreePtr, ItemType& inorderSuccessor);
    
    // Returns a pointer to the node containing the given value, or nullptr if not found.
    auto findNode(BinaryNode<ItemType> *subTreePtr, const ItemType& target) const;

    //Copies the tree rooted at treePtr and returns a pointer to the root of the tree
    auto copyTree(const BinaryNode<ItemType> *oldTreeRootPtr) const;

    //Recursively deletes all nodes from the tree
    void destroyTree(BinaryNode<ItemType> *subTreePtr);

    //Traversal Methods
    void preorder(BinaryNode<ItemType> *subTreePtr) const;
    void inorder(BinaryNode<ItemType> *subTreePtr) const;
    void postorder(BinaryNode<ItemType> *subTreePtr) const;

  public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------

    BinarySearchTree();
    BinarySearchTree(const ItemType& rootItem);
    BinarySearchTree(const BinarySearchTree<ItemType>& tree);
    virtual ~BinarySearchTree();

    //------------------------------------------------------------
    // Public Methods Section.
    //------------------------------------------------------------

    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;

    ItemType getRootData() const throw(PrecondViolatedExcept);
    void setRootData(const ItemType& newData);
    
    bool add(const ItemType& newEntry);
    bool remove(const ItemType& target);
    void clear();
    
    ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
    bool contains(const ItemType& anEntry) const;

    //------------------------------------------------------------
    // Public Traversals Section.
    //------------------------------------------------------------

    void preorderTraverse() const;
    void inorderTraverse() const;
    void postorderTraverse() const;
    
    //------------------------------------------------------------
    // Overloaded Operator Section.
    //------------------------------------------------------------

    BinarySearchTree<ItemType> &operator=(const BinarySearchTree<ItemType>& rightHandSide)
    {
      if (*this != rightHandSide)
      {
        this->rootPtr = rightHandSide->rootPtr;
        this->rootPtr.setLeftChildPtr(rightHandSide->getLeftChildPtr());
        this->rootPtr.setRightChildPtr(rightHandSide->getRightChildPtr());
      } //Faulty implementation but not necessary for driver
    }
}; // end BinarySearchTree

//Get Height Helper
template<class ItemType>
int BinarySearchTree<ItemType>::getHeightHelper(BinaryNode<ItemType> *subTreePtr) const
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
int BinarySearchTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType> *subTreePtr) const
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
template<class ItemType>
auto BinarySearchTree<ItemType>::balancedAdd(BinaryNode<ItemType> *subTreePtr, BinaryNode<ItemType> *newNodePtr)
{
  if (subTreePtr == nullptr)
  {
    return newNodePtr;
  }
  else
  {
    BinaryNode<ItemType> *leftPtr = subTreePtr->getLeftChildPtr();
    BinaryNode<ItemType> *rightPtr = subTreePtr->getRightChildPtr();

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
}

//Place node
template<class ItemType>
auto BinarySearchTree<ItemType>::placeNode(BinaryNode<ItemType> *subTreePtr, BinaryNode<ItemType> *newNodePtr)
{
  BinaryNode<ItemType> *tempPtr = nullptr;
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
}

//Remove Value
template<class ItemType>
auto BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType> *subTreePtr, const ItemType target, bool &isSuccessful)
{
  BinaryNode<ItemType> *tempPtr = nullptr;
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
}

//Remove Node
template<class ItemType>
auto BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType> *nodePtr)
{
  BinaryNode<ItemType> *tempPtr = nullptr;
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
}

//Remove Left Most Node
template<class ItemType>
auto BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType> *nodePtr, ItemType &inorderSuccessor)
{
  BinaryNode<ItemType> *tempPtr = nullptr;
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
}

//Find node
template<class ItemType>
auto BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType> *subTreePtr, const ItemType &target) const
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
}

//Copy Tree
template<class ItemType>
auto BinarySearchTree<ItemType>::copyTree(const BinaryNode<ItemType> *oldTreeRootPtr) const
{
  BinaryNode<ItemType> *newTreePtr = nullptr;

  //Copy tree nodes during preorder traversal
  if (oldTreeRootPtr != nullptr)
  {
    //Copy the node
    newTreePtr = new BinaryNode<ItemType>(oldTreeRootPtr->getItem(), nullptr, nullptr);
    newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
    newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
  }

  //Else tree is empty (newTreePtr is nullptr)
  return newTreePtr;
}

//Destroy Tree
template<class ItemType>
void BinarySearchTree<ItemType>::destroyTree(BinaryNode<ItemType> *subTreePtr)
{
  if (subTreePtr != nullptr)
  {
    destroyTree(subTreePtr->getLeftChildPtr());
    destroyTree(subTreePtr->getRightChildPtr());
    subTreePtr.reset(); //Decrement reference count to node. std::shared_ptr::reset()
  }
}

//Preorder helper
template<class ItemType>
void BinarySearchTree<ItemType>::preorder(BinaryNode<ItemType> *subTreePtr) const
{
  if(subTreePtr != nullptr)
  {
    cout << subTreePtr->getItem() << " ";
    preorder(subTreePtr->getLeftChildPtr());
    preorder(subTreePtr->getRightChildPtr());
  }
}

//Inorder helper
template<class ItemType>
void BinarySearchTree<ItemType>::inorder(BinaryNode<ItemType> *subTreePtr) const
{
  if(subTreePtr != nullptr)
  {
    inorder(subTreePtr->getLeftChildPtr());
    cout << subTreePtr->getItem() << " ";
    inorder(subTreePtr->getRightChildPtr());
  }
}

//Postorder helper
template<class ItemType>
void BinarySearchTree<ItemType>::postorder(BinaryNode<ItemType> *subTreePtr) const
{
  if(subTreePtr != nullptr)
  {
    postorder(subTreePtr->getLeftChildPtr());
    postorder(subTreePtr->getRightChildPtr());
    cout << subTreePtr->getItem() << " ";
  }
}

//Default
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
}

//Parameterized
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem)
{
  this->rootPtr = new BinaryNode<ItemType>(rootItem);
}

//Copy
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &tree)
{
  this->rootPtr = copyTree(tree.rootPtr);
}

//Destructor
template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
  this->clear();
  this->rootPtr = nullptr;
  delete this->rootPtr;
}

//Is Empty
template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
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

//Get Height (conv)
template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
  return getHeightHelper(this->rootPtr); //From BinaryNodeTree
}

//Get Number of Nodes
template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
  return getNumberOfNodesHelper(this->rootPtr); 
}

//Get Root Data
template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
  if (this->rootPtr == nullptr)
  {
    throw "Root does not exist!";
  }
  return rootPtr->getItem();
}

//Set Root Data
template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType &newData)
{
  rootPtr->setItem(newData);
}

//Add
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newData)
{
  BinaryNode<ItemType> *newNodePtr = new BinaryNode<ItemType>(newData);
  this->rootPtr = placeNode(rootPtr, newNodePtr);
  return 1;
}

//Remove
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &target)
{
  bool isSuccessful = 0;
  this->rootPtr = removeValue(this->rootPtr, target, isSuccessful);
  return isSuccessful;
}

//Clear
template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
  if(this->rootPtr != nullptr)
  {
    removeNode(rootPtr->getLeftChildPtr());
    removeNode(rootPtr->getRightChildPtr());

    rootPtr->setLeftChildPtr(nullptr);
    rootPtr->setRightChildPtr(nullptr);

    delete this->rootPtr;
    this->rootPtr = nullptr;
  }
  this->rootPtr = nullptr;
}

//Get Entry
template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const throw(NotFoundException)
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
}

//Contains
template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const
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
}

//Preorder traverse
template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse() const
{
  preorder(this->rootPtr);
}


//Inorder traverse
template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse() const
{
  inorder(this->rootPtr);
}

//Postorder traverse
template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse() const
{
  postorder(this->rootPtr);
}

/*//Overloaded assignment (incp)
template<class ItemType>
BinarySearchTree<ItemType>::&operator=(const BinarySearchTree<ItemType> &rightHandSide)
{
  if (*this != rightHandSide)
  {
    this->rootPtr = rightHandSide->rootPtr;
    this->rootPtr.setLeftChildPtr(rightHandSide->getLeftChildPtr());
    this->rootPtr.setRightChildPtr(rightHandSide->getRightChildPtr());
  } //Faulty implementation but not necessary for driver
}*/

#endif