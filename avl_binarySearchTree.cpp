#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <sys/stat.h>
#include <exception>
#include <cerrno>
#include <cstring>

#include "avl_binarySearchTree.h"
#include "customErrorClass.h"

using namespace std;

/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To initialize the root node and the node count.
**    Function Output: Nothing.
**    Side Effects: Nothing
*/
c_AVL_BinarySearchTree::c_AVL_BinarySearchTree()
{
  this->root = NULL;
  this->nodeCount = 0;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To deallocate memory, call the deleteTree function, and do cleanup of the tree.
**    Function Output: Nothing.
**    Side Effects: Nothing.
*/
c_AVL_BinarySearchTree::~c_AVL_BinarySearchTree()
{
  deleteTree();
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**                  To call the p_deleteNode function.
**    Function Output: Nothing.
**    Side Effects: To pass the integer value entered into the p_deleteNode function. 
**                  Throw an error if the tree is empty.
*/
void c_AVL_BinarySearchTree::deleteValue(int val)
{
  if (this->nodeCount == 0)
  {
    throw MyException("ERROR: Cannot delete a node from an empty tree.");
  }
  s_NODE *node = this->p_createNode(val);
  this->p_deleteNode(this->root, node);
  this->nodeCount--;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_deleteTree function.
**    Function Output: Nothing.
**    Side Effects: Throw an error if the tree is empty.
*/

void c_AVL_BinarySearchTree::deleteTree()
{
  if (this->nodeCount == 0)
  {
    throw MyException("ERROR: Cannot delete an empty tree.");
  }
  this->p_deleteTree(this->root);
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_findNode function.
**    Function Output: Nothing.
**    Side Effects: To pass an integer value into the p_findNode function and return the node. Throw an error is the tree is empty.
*/
s_NODE *c_AVL_BinarySearchTree::findNode(int value)
{
  if (value < 0)
  {
    throw MyException("ERROR: Cannot enter a negative value.");
  }
  s_NODE *temp = this->p_findNode(this->root, value);
  return temp;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_getHeight function.
**    Function Output:
**    Side Effects: To pass the root into the p_height function and return the height as an integer. 
**                  Throw an error if the tree is empty.
*/
int c_AVL_BinarySearchTree::height()
{
  if (this->nodeCount == 0)
  {
    throw MyException("ERROR: Cannot calculate of height of empty tree.");
  }
  return this->p_height(this->root);
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To validate input at the command line. 
**    Function Output:
**    Side Effects: To throw an error if the file does not exist, the file is empty or the a file name is not entered in the command line.
**                  Return true if it passes validation. Return false if it does not.
*/
bool c_AVL_BinarySearchTree::inputValidation(int argc, char *argv[])
{

  bool retValue = false;
  struct stat fileInfo;
  string errorString;
  int error;

  if (argc <= 1)
  {
    throw MyException("ERROR: Command line should have two arguments.");
  }
  error = stat(argv[1], &fileInfo);
  if (0 != error)
  {
    errorString = strerror(errno);
    errorString += ": ";
    errorString += argv[1];
    throw runtime_error(errorString);
  }

  if (0 == fileInfo.st_size)
  {
    errorString += "file is empty: ";
    errorString += argv[1];
    throw runtime_error(errorString);
  }

  retValue = true;

  return retValue;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           To call the p_insertValue function.
**    Function Output: Nothing.
**    Side Effects: 
**           Create a new node and pass the integer value into the p_insertValue function.
**           If the root is NULL, then the node equals this->root. Increase the node count by one each time a node is inserted.
**           Pass the root intot the p_height function.
*/
void c_AVL_BinarySearchTree::insertValue(int value)
{

  if (value < 0)
  {
    throw MyException("ERROR: Cannot enter a negative value.");
  }

  if (this->p_contains(value))
  {
    cout << "Insert: value " << value << " ...already exists; not inserting." << endl;
  }

  s_NODE *node = this->p_createNode(value);

  if (this->root == NULL)
  {
    this->root = node;
  }
  else
  {
    this->p_insertValue(this->root, node);
    this->nodeCount++;
    height();
  }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To call the p_printTree function.
**    Function Output: Nothing.
**    Side Effects: Throw an error if the tree is empty.
*/
void c_AVL_BinarySearchTree::printTree()
{
  if (0 == this->nodeCount)
  {
    throw MyException("ERROR: Cannot print from an empty tree.");
  }
  else
  {
    this->p_printTree(this->root, this->nodeCount);
    cout << "\n"
         << endl;
  }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To read the file, check each integer and determine what command it is.
**    Function Output: Nothing.
**    Side Effects: 
**        To open the file, read the file, check integers and determine the command, execute the command, close the file.
*/
void c_AVL_BinarySearchTree::readFile(string fileName)
{
  if (fileName.length() == 0)
  {
    throw MyException("ERROR: Please enter a file Name.");
  }
  ifstream inputFile;
  int command;

  inputFile.open(fileName);
  bool shouldExit = false;

  if (inputFile.is_open())
  {

    while (!shouldExit && !inputFile.eof())
    {

      inputFile >> command;

      switch (command)
      {
      case 0:
        int val;
        inputFile >> val;
        insertValue(val);
        break;
      case 1:
        int value;
        inputFile >> value;
        deleteValue(value);
        break;
      case 2:
        printTree();
        break;
      case 8:
        deleteTree();
        break;
      case 9:
        cout << "QUITING..." << endl;
        shouldExit = true;
        break;
      }
    }
  }
  inputFile.close();
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To determine if a node exist or not.
**    Function Output:
**    Side Effects: Return true if the node exist, return false if it does not exist.
**                  Throw an error if the tree is empty.
*/
bool c_AVL_BinarySearchTree::p_contains(int value)
{
  if (value < 0)
  {
    throw MyException("ERROR: Cannot enter a negative value");
  }
  if (findNode(value) != NULL)
  {
    return true;
  }
  return false;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          To create new nodes.
**    Function Output: Nothing.
**    Side Effects: 
**          Create a new node that is dynamically store, set the leftChild and rightChildChild pointer to NULL, and return newly create node. 
**          Throw an exception error if a negative value is entered by user. 
*/
s_NODE *c_AVL_BinarySearchTree::p_createNode(int value)
{
  if (value < 0)
  {
    throw MyException("ERROR: Cannot enter a negative value.");
  }

  s_NODE *temp = new s_NODE;

  temp->value = value;
  temp->leftChild = NULL;
  temp->rightChild = NULL;
  temp->height = 0;

  return temp;
}
/*
**    Author: Berlin Johnson
**    Function Purpose:
**        To delete an arbitrary node.
**    Function Output:
**    Side Effects: Traverse the tree, find the node, find the successor, swap the value and delete the node. Throw an exception error if the tree is empty.
**    
**                  I used https://www.geeksforgeeks.org/avl-tree-set-2-deletion/ as a reference to build p_deleteNode.
**                  I followed same format: Traverse the tree, if the node has one child set temp equal to the child, if it has
**                  no child temp equal to node and node equal to null. Swap the values and delete temp node. Find the sucessor
**                  and copy the successor node data to node and delete the sucessor. Update the height. Get the balace factor.
**                  Check each case by the balance factor.
*/
s_NODE *c_AVL_BinarySearchTree::p_deleteNode(s_NODE *parent, s_NODE *node)
{
  if (node == NULL)
  {
    throw MyException("ERROR: Cannot delete an empty node.");
  }

  if (node->value < parent->value)
  {
    parent->leftChild = this->p_deleteNode(parent->leftChild, node);
  }
  else if (node->value > parent->value)
  {
    parent->rightChild = this->p_deleteNode(parent->rightChild, node);
  }
  else
  {
    s_NODE *temp = NULL;
    if (parent->leftChild = NULL)
    {
      temp = node->rightChild;
    }
    else if (parent->rightChild == NULL)
    {
      temp = node->leftChild;
    }
    else
    {
      temp = node;
      node = NULL;
    }
    if (parent->leftChild == NULL || parent->rightChild == NULL)
    {

      *node = *temp;
      free(temp);
    }
    if (parent->leftChild != NULL && parent->rightChild != NULL)
    {
      s_NODE *successorN = this->p_successor(node->rightChild);
      node->value = successorN->value;
      node->rightChild = this->p_deleteNode(node->rightChild, successorN->rightChild);
    }
    node->height = 1 + this->p_maxValue(this->p_height(node->leftChild), this->p_height(node->rightChild));
    int balanceFactor = this->p_heightDifference(node);

    if (balanceFactor < 1 && this->p_heightDifference(node->leftChild) >= 0)
    {
      return this->p_rotateRight(node);
    }

    if (balanceFactor > 1 && this->p_heightDifference(node->leftChild) < 0)
    {
      node->leftChild = this->p_rotateLeft(node->leftChild);
      return this->p_rotateRight(node);
    }

    if (balanceFactor < -1 && this->p_heightDifference(node->rightChild) <= 0)
    {
      return this->p_rotateRight(node);
    }

    if (balanceFactor < -1 && this->p_heightDifference(node->rightChild) > 0)
    {
      node->rightChild = this->p_rotateRight(node->rightChild);
      return this->p_rotateLeft(node);
    }
  }
  return node;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**        To delete the entire binary Tree.
**    Function Output:
**    Side Effects: To traverse through binary Search Tree and delete every node. Throw an exception error if the tree is empty.
*/
void c_AVL_BinarySearchTree::p_deleteTree(s_NODE *node)
{
  if (this->nodeCount == 0)
  {
    throw MyException("ERROR: Cannot delete an empty tree.");
  }
  if (node != NULL)
  {
    this->p_deleteTree(node->leftChild);
    this->p_deleteTree(node->rightChild);
    delete node;
  }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          To traverse the tree and return the node if it is found, otherwise return NULL.
**    Function Output:
**    Side Effects: 
**          Create new node and pass the value into it. Check if the value enter matches a node in the tree.
**          Traverse both sides of the tree and return the node if found. Throw an exception error is the tree is empty.
*/
s_NODE *c_AVL_BinarySearchTree::p_findNode(s_NODE *node, int value)
{
  if (value < 0)
  {
    throw MyException("ERROR: Cannot enter negative values to find.");
  }
  if (NULL == node || node->value == value)
  {
    return node;
  }
  else
  {
    if (value < node->value)
    {

      return this->p_findNode(node->leftChild, value);
    }
    else if (value > node->value)
    {

      return this->p_findNode(node->rightChild, value);
    }
  }
  return node;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           To traverse the tree and get height of the tree.
**    Function Output: Nothing.
**    Side Effects: 
**          Return zero if the tree is empty. Traverse through the tree and store the height on boths sides. 
**          Compare the height on both sides and return the highest height. Throw an exception error if the tree is empty.
*/
int c_AVL_BinarySearchTree::p_height(s_NODE *node)
{
  if(this->nodeCount == 0){
    //throw MyException("ERROR: Cannot get height of empty tree.");
  }
  int lHeight = 0;
  int rHeight = 0;
  if (node == NULL)
  {
    return 0;
  }

  if (node->leftChild == NULL)
  {
    lHeight = 0;
  }
  else
  {
    lHeight = this->p_height(node->leftChild) + 1;
  }

  if (node->rightChild == NULL)
  {
    rHeight = 0;
  }
  else
  {
    rHeight = this->p_height(node->rightChild) + 1;
  }

  node->height = this->p_maxValue(lHeight, rHeight);
  return node->height;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           To get the difference in heights of the left and right subtree.
**    Function Output: Nothing.
**    Side Effects: To subtract the height of the left subtree from the height of the right subtree.
**
**                  I used https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ as a reference to design the function. I followed the same
**                  structure if the node is null return 0. Subtract the left and right subtree height. 
**           
*/
int c_AVL_BinarySearchTree::p_heightDifference(s_NODE *node)
{
  if (0 == this->nodeCount)
  {
    //throw MyException("ERROR: Cannot get height difference from an empty tree.");
  }

  if (node == NULL)
  {
    return 0;
  }
  return this->p_height(node->leftChild) - this->p_height(node->rightChild);
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           To check the tree balance and determine which insertion case should be used.
**    Function Output: Nothing.
**    Side Effects: Check the height difference and check each case by the height difference and execute the case algorithm.
**            
**                  I used https://www.geeksforgeeks.org/avl-tree-set-2-deletion/ as a reference. Get the balance factor and check each base to 
**                  determine which one to execute.
*/
s_NODE *c_AVL_BinarySearchTree::p_insertCase(s_NODE *parent, s_NODE *node)
{

  int balanceFactor = this->p_heightDifference(parent);

  if (balanceFactor > 1 && node->value < parent->leftChild->value)
  {
    return this->p_rotateRight(parent);
  }

  if (balanceFactor > 1 && node->value > parent->rightChild->value)
  {
    return this->p_rotateLeft(parent);
  }

  //left right case
  if (balanceFactor < -1 && node->value > parent->leftChild->value)
  {
    parent->leftChild = this->p_rotateLeft(parent->leftChild);
    return this->p_rotateRight(parent);
  }

  // right left case
  if (balanceFactor < -1 && node->value < parent->rightChild->value)
  {
    parent->rightChild = this->p_rotateRight(parent->rightChild);
    return this->p_rotateLeft(parent);
  }
  return parent;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           Insert a node into the binary search tree.
**    Function Output: Nothing.
**    Side Effects: 
**           Traverse the tree insert the node on the leftChild side if less than parent value, store on the rightChild side if greater
**           than parent node, return the parent node.      
*/
s_NODE *c_AVL_BinarySearchTree::p_insertValue(s_NODE *parent, s_NODE *node)
{
  if (NULL == node)
  {
    throw MyException("ERROR: The node entered is empty.");
  }
  if (NULL == parent)
  {
    return node;
  }
  else
  {
    if (node->value < parent->value)
    {
      parent->leftChild = this->p_insertValue(parent->leftChild, node);
    }
    else if (node->value > parent->value)
    {
      parent->rightChild = this->p_insertValue(parent->rightChild, node);
    }
  }
  parent->height = 1 + this->p_maxValue(this->p_height(parent->leftChild), this->p_height(parent->rightChild));
  this->p_insertCase(parent, node);

  return parent;
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**           To get the highest height value of the left and right subtree.
**    Function Output: Nothing.
**    Side Effects: Return the greatest value between the left and right subtree.
**
**                  I used https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ as a reference to design the function. I followed the same
**                  structure. Compare the height of the left and right subtree and return the greatest value.
**           
*/
int c_AVL_BinarySearchTree::p_maxValue(int lHeight, int rHeight)
{
  if (0 == this->nodeCount)
  {
    //throw MyException("ERROR: Cannot return max height value from an empty tree.");
  }
  return (lHeight > rHeight) ? lHeight : rHeight;
}
/*
**    Author: Berlin Johnson
**    Function Purpose:
**          Find the predecessor node.
**    Function Output: Nothing.
**    Side Effects: Find and return the maximum value in the subtree.
**
**                  I used https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/BST.java.html as a reference. I followed the max function
**                  to find the largest node in the right subtree.
*/
s_NODE *c_AVL_BinarySearchTree::p_predecessor(s_NODE *node)
{

  if (node->rightChild == NULL)
  {
    return node;
  }
  else
  {
    return this->p_predecessor(node->rightChild);
  }
}
/*
**    Author: Berlin Johnson
**    Function Purpose: 
**          Display the binary search tree in a format.
**    Function Output: Nothing.
**    Side Effects: 
**          Perform inorder traversal and print the nodes and the height to the screen. Throw an exception error is the tree is empty.
*/
void c_AVL_BinarySearchTree::p_printTree(s_NODE *node, int indent)
{

  if (NULL != node)
  {
    if (0 == this->nodeCount)
    {
      throw MyException("ERROR: Cannot print in format from an empty tree.");
    }
    if (NULL != node)
    {
      this->p_printTree(node->leftChild, indent + 4);
      if (indent)
      {
        cout << setw(indent) << " ";
      }
      cout << node->value << " RHeight : " << this->p_height(node) << " LHeight: " << this->p_height(node) << endl;
      this->p_printTree(node->rightChild, indent + 4);
    }
  }
}
/*
**    Author: Berlin Johnson
**    Function Purpose:
**          Rotate the given node to the left.
**    Function Output: Nothing.
**    Side Effects: Rotate the node to the left. Update the height of the parent and child node. Return the child node.
**
*/
s_NODE *c_AVL_BinarySearchTree::p_rotateLeft(s_NODE *node)
{
  if (node == NULL)
  {
    throw MyException("ERROR: Cannot rotate left an empty node.");
  }
  s_NODE *parent = node;
  s_NODE *child = parent->rightChild;

  parent->rightChild = child->leftChild;
  child->leftChild = parent;

  parent->height = this->p_maxValue(this->p_height(parent->leftChild), this->p_height(parent->rightChild)) + 1;
  child->height = this->p_maxValue(this->p_height(child->leftChild), this->p_height(child->rightChild)) + 1;

  return child;
}
/*
**    Author: Berlin Johnson
**    Function Purpose:
**          Rotate the given node to the right.
**    Function Output: Nothing.
**    Side Effects: Rotate the node to the right. Update the height of the parent and child node. Return the child node.
**
*/
s_NODE *c_AVL_BinarySearchTree::p_rotateRight(s_NODE *node)
{
  if (node == NULL)
  {
    throw MyException("ERROR: Cannot rotate right an empty node.");
  }
  s_NODE *parent = node;
  s_NODE *child = parent->leftChild;

  parent->leftChild = child->rightChild;
  child->rightChild = parent;

  parent->height = this->p_maxValue(this->p_height(parent->leftChild), this->p_height(parent->rightChild)) + 1;
  child->height = this->p_maxValue(this->p_height(child->leftChild), this->p_height(child->rightChild)) + 1;

  return child;
}
/*
**    Author: Berlin Johnson
**    Function Purpose:
**          Find the successor node.
**    Function Output: Nothing.
**    Side Effects: Find and return the minimum value in the subtree.
**
**                  I used https://algs4.cs.princeton.edu/code/edu/princeton/cs/algs4/BST.java.html as a reference. I followed the min function
**                  to find the largest node in the right subtree.
*/
s_NODE *c_AVL_BinarySearchTree::p_successor(s_NODE *node)
{
  if (node->leftChild == NULL)
  {
    return node;
  }
  else
  {
    return this->p_successor(node->leftChild);
  }
}
