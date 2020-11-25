#include <iostream>
#include <ctime>
#include "BinarySearchTree.h"

using namespace std;

const int lo = 1;
const int hi = 200;
const int amt = 100;

int generateRandom(const int min, const int max);

int main()
{
  BinarySearchTree<int> tree;
  int numbers[amt];
  char userInput = 'n';

  srand(time(NULL));
  for (int x=0; x<amt; x++)
  {
    numbers[x] = generateRandom(lo, hi);
    tree.add(numbers[x]);
  }

  cout << "Height of tree: " << tree.getHeight();
  cout << endl << endl << "Preorder Traversal" << endl;
  tree.preorderTraverse();
  cout << endl << endl << "Inorder Traversal" << endl;
  tree.inorderTraverse();
  cout << endl << endl << "Postorder Traversal" << endl;
  tree.postorderTraverse();

  cout << endl << endl << "Print array of numbers? [y/n] ";
  cin >> userInput;
  if (userInput == 'y')
  {
    for (int y=0; y<amt; y++)
    {
      cout << numbers[y] << ' ';
    }
    cout << endl;
  }
  return 0;
}

int generateRandom(const int min, const int max)
{
  int btwn = max - min;
  return (rand() % btwn) + min;
}