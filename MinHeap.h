#ifndef MINHEAP_H
#define MINHEAP_H
#include <vector>
#include "TreeNode.h"
#include <climits>
#include <string>

using namespace std;

class MinHeap
{
        private:
  //int heap_size;
  //vector<TreeNode*> heapyBoy;
  //vector<TreeNode*>::iterator it;
        public:
  int heap_size;
  vector<TreeNode*> heapyBoy;
                MinHeap();
                void MinHeapify(int);
                TreeNode * removeMin(); //returns root of heap
                void insert(TreeNode * val); //adds element to heap
                int getSize(); //returns size of heap
                ~MinHeap();
};

#endif

