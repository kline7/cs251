ifndef HUFFTREE_H
#define HUFFTREE_H

#include "MinHeap.h"
#include "TreeNode.h"
#include <string>

#define MAXCODELENGTH 256
#define BYTESIZE 8

using namespace std;

class HuffTree
{
 private:
  //Add class members and methods                                                                                                                                                                                                                                                                                                                                           
  void codeGenerator(TreeNode *r, string t);
  TreeNode * root;
  vector<string> bitCodes;
 public:
  HuffTree();
  int getCharVecSize();
  //build a hiffman  tree  give a minheap                                                                                                                                                                                                                                                                                                                                   
  void buildTree(MinHeap * mh);

  //generate codes by traversing the huffman tree                                                                                                                                                                                                                                                                                                                           
  //and store them in an internal data structure (array of strings for example)                                                                                                                                                                                                                                                                                             
  void generateCodes();
  //void generateCodes(TreeNode *r, string t);                                                                                                                                                                                                                                                                                                                              
  //returns root of the tree                                                                                                                                                                                                                                                                                                                                                
  TreeNode * getRoot();
  TreeNode * newNode(char data, unsigned int  freq);
  //returns huffman code from  the ascii code                                                                                                                                                                                                                                                                                                                               
  string getCharCode(int c);
  int arr[1000];
  vector<char> charHolder;
  ~HuffTree();

};


#endif
