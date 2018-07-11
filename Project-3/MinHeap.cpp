include <iostream>
#include <climits>
#include <cstring>
#include <cstdint>
#include "MinHeap.h"
#define ARRAYMAX 1000;
using namespace std;


//implement the methods in MinHeap.h                                                                                                                                                                                                                                                                                                                                        
//constructor                                                                                                                                                                                                                                                                                                                                                               
MinHeap::MinHeap()
{
  numElements = 0;
}
//insert to minheap                                                                                                                                                                                                                                                                                                                                                         
void MinHeap::insert(TreeNode * val)
{
  heapyBoy.push_back(val);
  numElements++;
  this->BubbleUp(numElements -1);
}
//destructor                                                                                                                                                                                                                                                                                                                                                                
MinHeap::~MinHeap(){
  for(int i =0; i < heapyBoy.size(); i++){
    delete heapyBoy[i];
  }
}
//returns size of minheap                                                                                                                                                                                                                                                                                                                                                   
int MinHeap::getSize()
{
  return this->numElements;
}
//remove the min node of the heap                                                                                                                                                                                                                                                                                                                                           
TreeNode * MinHeap::removeMin()
{
  if(numElements == 0)
    return NULL;
  TreeNode * temp = heapyBoy[0];
  heapyBoy[0] = heapyBoy[numElements-1];
  heapyBoy.erase(heapyBoy.end()-1);
  BubbleDown(0);
  numElements--;
  return temp;
}
//sift down the minheap                                                                                                                                                                                                                                                                                                                                                     
void MinHeap::BubbleDown(int index){
  int leftChild = this->lChildIndex(index);
  int rightChild = this->rChildIndex(index);
  int minIndex = index;
  if(leftChild < numElements){
    if(heapyBoy[leftChild]->getFrequency() < heapyBoy[index]->getFrequency())
      minIndex = leftChild;
  }
  if(rightChild < numElements){
    if( heapyBoy[rightChild]->getFrequency() < heapyBoy[minIndex]->getFrequency())
      minIndex = rightChild;
  }
  if(minIndex != index){
    swap(minIndex, index);
    BubbleDown(minIndex);
  }
}
//sift node up the heap                                                                                                                                                                                                                                                                                                                                                     
void MinHeap::BubbleUp(int index){
  int child = numElements -1;
  int parent = this->parentIndex(index);
  while(child > 0){
    if(heapyBoy[child]->getFrequency() >= heapyBoy[parent]->getFrequency() )
      break;
    swap(child, parent);
    child = parent;
    parent = this->parentIndex(child);
  }
}
//utility func to swap                                                                                                                                                                                                                                                                                                                                                      
void MinHeap::swap(int child, int parent){
  TreeNode * temp = heapyBoy[child];
  heapyBoy[child] = heapyBoy[parent];
  heapyBoy[parent] = temp;
}
//utility func to get index                                                                                                                                                                                                                                                                                                                                                 
int MinHeap::parentIndex(int childIndex){
  return (childIndex-1)/2;
}

int MinHeap::rChildIndex(int parentIndex){
  return 2*parentIndex +2;
}

int MinHeap::lChildIndex(int parentIndex){
  return 2*parentIndex +1;
}
