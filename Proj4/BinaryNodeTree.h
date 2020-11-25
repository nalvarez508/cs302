#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"

using namespace std;

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
  private:
    shared_ptr<BinaryNode<ItemType>> rootPtr;
  protected:
    //Utility methods, Recursive helper methods
    int getHeightHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
    int getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const;

    //Recursively adds new node to tree in left/right fashion to keep balance
    auto balancedAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr, shared_ptr<BinaryNode<Item Type>> newNodePtr);

    //Removes the target value from the tree
    virtual auto removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool &isSuccessful);

    //Copies values up the tree to overwrite value in current node until a leaf is found. The leaf is then removed, since its value is stored in the parent.
    auto moveValuesUpTree(shared_ptr<BinaryNode<ItemType>> subTreePtr);

    //Recursively searches for target value
    virtual auto findNode(shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType &target, bool &isSuccessful) const;

    //Copies the tree rooted at treePtr and returns a pointer to the root of the tree
    auto copyTree(const shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const;

    //Recursively deletes all nodes from the tree
    void destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr);

    //Recursive traversal helper methods
    void preorder(void std::visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const;
    void inorder(void std::visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const;
    void postorder(void std::visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const;

  public:
    //Constructors and Destructors
    BinaryNodeTree();
    BinaryNodeTree(const ItemType &rootItem);
    BinaryNodeTree(const ItemType &rootItem, const shared_ptr<BinaryNode<ItemType>> leftTreePtr, const shared_ptr<BinaryNode<ItemType>> rightTreePtr);
    BinaryNodeTree(const shared_ptr<BinaryNode<ItemType>> &tree);
    virtual ~BinaryNodeTree();

    //Interface methods
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    ItemType getRootData() const/* throw(PrecondViolatedExcept)*/;
    bool add(const ItemType &newData); //Adds item to tree
    bool remove(const ItemType &data); //Removes item from tree
    void clear();
    ItemType getEntry(const ItemType &anEntry) const/* throw(NotFoundException)*/;
    bool contains(const ItemType &anEntry);

    //Traversal
    void preorderTraverse(void std::visit(ItemType&)) const;
    void inorderTraverse(void std::visit(ItemType&)) const;
    void postorderTraverse(void std::visit(ItemType&)) const;

    //Overloaded operator
    BinaryNodeTree &operator=(const BinaryNodeTree &rightHandSide);
};

//Height helper
template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
  if (subTreePtr == nullptr)
  {
    return 0;
  }
  else
  {
    return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr())); //where is max?
  }
}

//Balanced add
template<class ItemType>
auto BinaryNodeTree<ItemType>::balancedAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr, shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
  if (subTreePtr == nullptr)
  {
    return newNodePtr;
  }
  else
  {
    auto leftPtr = subTreePtr->getLeftChildPtr();
    auto rightPtr = subTreePtr->getRightChildPtr();

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

//Copy Tree
template<class ItemType>
shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::copyTree(const shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const
{
  shared_ptr<BinaryNode<ItemType>> newTreePtr;

  //Copy tree nodes during preorder traversal
  if (oldTreeRootPtr != nullptr)
  {
    //Copy the node
    newTreePtr = make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem(), nullptr, nullptr);
    newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
    newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
  }

  //Else tree is empty (newTreePtr is nullptr)
  return newTreePtr;
}

//Destroy Tree
template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
  if (subTreePtr != nullptr)
  {
    destroyTree(subTreePtr->getLeftChildPtr());
    destroyTree(subTreePtr->getRightChildPtr());
    subTreePtr.reset(); //Decrement reference count to node. Also, where is reset function?
  }
}

//Inorder
template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void std::visit(ItemType&), shared_ptr<BinaryNode<ItemType>> treePtr) const
{
  if (treePtr != nullptr)
  {
    inorder(std::visit, treePtr->getLeftChildPtr());
    ItemType theItem = treePtr->getItem();
    std::visit(theItem);
    inorder(std::visit, treePtr->getRightChildPtr());
  }
}

//Default
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
}

//Parameterized
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem) : rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{
}

//Copy
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem, const shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr, const shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr) : rootPtr(make_shared<BinaryNode<ItemType>>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr)))
{ 
}

//Tree
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType> &tree)
{
  rootPtr = copyTree(tree.rootPtr);
}

//Add
template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType &newData)
{
  auto newNodePtr = make_shared<BinaryNode<ItemType>>(newData);
  rootPtr = balancedAdd(rootPtr, newNodePtr);
  return 1;
}

#endif