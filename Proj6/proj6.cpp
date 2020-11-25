#include <iostream>
#include "LLRBtree.h"

using namespace std;

const int AMT = 10;
const int MIN = 1;
const int MAX = 200;

int generateRandom(const int min, const int max);

int main()
{
  srand(time(NULL));

  LeftLeaningRedBlackTree<int> tree;
  int add, rmv;
  //int testArr[10] = {157, 5, 125, 59, 20, 81, 79, 146, 145, 97};

  for (int i=0; i < AMT; i++)
  {
    add = generateRandom(MIN, MAX);
    //add = testArr[i];
    if (i == 4) //Flag our element for deletion
    {
      rmv = add;
    }
    cout << "Add " << add << " to tree" << endl;
    tree.add(add);
  }

  cout << endl << "Preorder Traversal" << endl;
  tree.preorderTraverse();
  cout << endl;

  cout << endl << "Remove " << rmv << " from tree" << endl << endl << "Preorder Traversal" << endl;
  tree.remove(rmv);
  tree.preorderTraverse();
  cout << endl;

  return 0;
}

int generateRandom(const int min, const int max)
{
  int btwn = max - min;
  return (rand() % btwn) + min;
}