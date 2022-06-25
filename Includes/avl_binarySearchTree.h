#ifndef __AVL_BinarySearchTree__
#define __AVL_BinarySearchTree__

#include <iostream>

using namespace std;

struct s_NODE {
  int value;
  s_NODE *left;
  s_NODE *right;
};

class c_AVL_BinarySearchTree {
  public:
    c_AVL_BinarySearchTree();
    ~c_AVL_BinarySearchTree();

    void deleteValue(int);
    void insertValue(int);
    void printTree();
    void readFile();
    void stopReadingFile();

  private:
    s_NODE *root;
    int nodeCount;

    s_NODE *p_insertNode(s_NODE*, s_NODE*);
    s_NODE *p_deleteNode(s_NODE*, s_NODE*);
    void p_printTree(s_NODE*);
    void p_readFile();
    void p_stopReadingFile();

};



#endif