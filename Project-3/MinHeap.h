#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"
#include <vector>

#define ARRAYMAX 1000;
using namespace std;

class MinHeap
{
 private:
  vector<TreeNode*> heapyBoy;
  int numElements;
 public:
  MinHeap();
  void swap(int child, int parent);
  TreeNode * removeMin(); //returns root of heap                                                                                                                                                                                                                                                                                                                            
  void insert(TreeNode * val); //adds element to heap                                                                                                                                                                                                                                                                                                                       
  int getSize(); //returns size of heap                                                                                                                                                                                                                                                                                                                                     
  void BubbleUp(int index);//sifts up                                                                                                                                                                                                                                                                                                                                       
  void BubbleDown(int index);//sifts down                                                                                                                                                                                                                                                                                                                                   
  int parentIndex(int index);//index of parent                                                                                                                                                                                                                                                                                                                              
  int rChildIndex(int index);//index of right child                                                                                                                                                                                                                                                                                                                         
  int lChildIndex(int index);//index of left child                                                                                                                                                                                                                                                                                                                          
  ~MinHeap();
};
#endif
