#ifndef BINARY_TREE_INTERFACE_
#define BINARY_TREE_INTERFACE_

#include "NotFoundException.h"

template<class ItemType>
class BinaryTreeInterface
{
  public:
    //Tests whether binary tree is empty
    virtual bool isEmpty() const = 0;

    //Gets height of binary tree
    virtual int getHeight() const = 0;

    //Gets number of nodes in binary tree
    virtual int getNumberOfNodes() const = 0;

    //Gets data in root of binary tree
    //pre: Binary tree is not empty
    //post: The root's data is returned, tree unchanged
    virtual ItemType getRootData() const = 0;

    //Replaces data in the root of binary tree with given data, or inserts node if tree is empty
    //pre: none
    //post: the data in the root is as given
    virtual bool setRootData(const ItemType &newData) = 0;

    //Adds given data to binary tree
    //post: binary tree contains new data
    virtual bool add(const ItemType &target) = 0;

    //Removes specified data from binary tree
    virtual bool remove(const ItemType &target) = 0;

    //Removes all data from this binary tree
    virtual void clear() = 0;

    //Retriees specified data from binary tree
    //post: Desired data is returned, tree is unchanged. Otherwise, error thrown
    virtual ItemType getEntry(const ItemType &target) const = 0;

    //Tests whether specified data is in binary tree
    //post: Tree is unchanged
    virtual bool contains(const ItemType &target) const = 0;

    //Traverses binary tree in preorder (inorder, postorder) and calls the function visit once for each node
    virtual void preorderTraverse(void visit(ItemType&)) const = 0;
    virtual void inorderTraverse(void visit(ItemType&)) const = 0;
    virtual void postorderTraverse(void visit(ItemType&)) const = 0;
    
    //Destroys tree and frees its assigned memory
    virtual ~BinaryTreeInterface(){}
};
#endif