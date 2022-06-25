#include <iostream>
#include <fstream>
#include "customErrorClass.h"
#include "avl_binarySearchTree.h"

using namespace std;

int main(int argc, char *argv[])
{
  c_AVL_BinarySearchTree bst;
  string fileName;
  bool retValue = false;

  ifstream inputFile;
 

  try
  {
    retValue = bst.inputValidation(argc, argv);
    fileName = argv[1];
    bst.readFile(fileName);
    
  }
  catch (MyException &e)
  {
    cout << e.what() << endl;
  }
  catch (runtime_error &e)
  {
    cout << "RUNTIME_ERROR: " << e.what() << endl;
  }
  catch (exception &e)
  {
    cout << "EXCEPTION: " << e.what() << endl;
  }
  

  if (true == retValue)
  {
    cout << "True" << endl;
  }
  else
  {
    cout << "False" << endl;
  }

  return 0;
}
