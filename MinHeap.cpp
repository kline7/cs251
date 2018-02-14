#include <iostream>
#include <climits>
#include <vector>
#include "MinHeap.h"



//implement the methods in MinHeap.h
using namespace std;
int parent(int i){return (i-1)/2;}
int left(int i){return (2*i +1);}
int right(int i){return (2*i +2);}

bool compare(TreeNode *l,TreeNode *r)
{
  return (l->getFrequency() > r->getFrequency());
}
void swap(TreeNode ** x, TreeNode **y){
  TreeNode * temp = *x;
  *x = *y;
  *y = temp;
}

int heap_size;
MinHeap::MinHeap()
{
  heap_size = 0;
}
void MinHeap::MinHeapify(int i)
{
  int l = left(i);
  int r = right(i);
  int smallest = i;
  if (l < heap_size && compare(heapyBoy[i],heapyBoy[l]))
    smallest = l;
  if (r < heap_size && compare(heapyBoy[smallest],heapyBoy[r]))
    smallest = r;
  if (smallest != i)
    {
      swap(&heapyBoy[i], &heapyBoy[smallest]);
      MinHeapify(smallest);
      }
}
void MinHeap::insert(TreeNode * val)
{
  //first insert the new key at the end
  heap_size++;
  int i = heap_size - 1;
  heapyBoy.push_back(val);
  //fix the min heap property if it is violated
  while ( i != 0 && compare(heapyBoy[parent(i)],heapyBoy[i]))
    {
      swap(&heapyBoy[i],&heapyBoy[parent(i)]);
      i = parent(i);
      }
}
int MinHeap::getSize()
{
        return heap_size;
}
TreeNode * MinHeap::removeMin()
{
  TreeNode * ret = NULL;
  if (heap_size <= 0)
    return NULL;
  if (heap_size == 1)
    {
      heap_size--;
      ret = heapyBoy[0];
      heapyBoy.erase (heapyBoy.begin());
      return ret;
    }
  //store min val, and remove it from heap
  TreeNode * min = heapyBoy[0];
  // cout<<" in mh v: "<<min->getVal()<<" f: "<<min->getFrequency()<<endl;
  //adding an erase
  //heapyBoy.erase (heapyBoy.begin());
  heapyBoy[0] = heapyBoy[heap_size-1];
  heap_size--;
  MinHeapify(0);
  heapyBoy.pop_back();
  return min;
}

