#ifndef __AVL_BinarySearchTree__
#define __AVL_BinarySearchTree__

#include <iostream>

using namespace std;

struct s_NODE
{
  int value;
  s_NODE *leftChild;
  s_NODE *rightChild;
  int height;
};

class c_AVL_BinarySearchTree
{
public:
  c_AVL_BinarySearchTree();
  ~c_AVL_BinarySearchTree();

  void deleteValue(int);
  void deleteTree();
  s_NODE *findNode(int);
  int height();
  bool inputValidation(int argc, char *argv[]);
  void insertValue(int);
  void printTree();
  void readFile(string fileName);

private:
  s_NODE *root;
  int nodeCount;

  bool p_contains(int);
  s_NODE *p_createNode(int);
  s_NODE *p_insertValue(s_NODE*, s_NODE*);
  s_NODE *p_deleteNode(s_NODE *, s_NODE*);
  void p_deleteTree(s_NODE *);
  s_NODE *p_findNode(s_NODE*, int);
  void p_fixHeight(s_NODE*, s_NODE*);
  int p_height(s_NODE*);
  int p_heightDifference(s_NODE*);
  s_NODE *p_insertCase(s_NODE*, s_NODE*);
  int p_maxValue(int, int);
  void p_printTree(s_NODE*, int);
  s_NODE *p_predecessor(s_NODE*);
  s_NODE *p_successor(s_NODE*);
  s_NODE* p_rotateRight(s_NODE*);
  s_NODE* p_rotateLeft(s_NODE*);
};

#endif