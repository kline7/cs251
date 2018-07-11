#include <iostream>
#include "HuffTree.h"
#include "TreeNode.h"
#include "MinHeap.h"

using namespace std;
//constructor                                                                                                                                                                                                                                                                                                                                                               
HuffTree::HuffTree(){
}
//return the root                                                                                                                                                                                                                                                                                                                                                           
TreeNode * HuffTree::getRoot(){
  return this->root;
}
//build the hufftree                                                                                                                                                                                                                                                                                                                                                        
void HuffTree::buildTree(MinHeap * mh){
  TreeNode * right;
  TreeNode * left;
  TreeNode * parent;
  for(int i = mh->getSize(); i > 1; i = mh->getSize()){
    left = mh->removeMin();
    right = mh->removeMin();
    parent = new TreeNode((char)(0), left->getFrequency() + right->getFrequency());
    parent->join(left,right);
    mh->insert(parent);
  }
  mh->removeMin();
  this->root = parent;
}
//recursive function to generate huff codes                                                                                                                                                                                                                                                                                                                                 
void HuffTree::generateCodes(){
  this->codeGenerator(this->getRoot(),"");
}
//return the size of charHolder vector                                                                                                                                                                                                                                                                                                                                      
int HuffTree::getCharVecSize(){
  return this->charHolder.size();
}
//delete all the nodes so no mem leaks                                                                                                                                                                                                                                                                                                                                      
void deleteNode(TreeNode *n){
  if(n->isLeafNode()){
    delete n;
  }
  else{
    deleteNode(n->getLeft());
    deleteNode(n->getRight());
    delete n;
  }
}
//recursive func to generate huff codes                                                                                                                                                                                                                                                                                                                                     
void HuffTree::codeGenerator(TreeNode * rootNode, string bitCode){

  if(rootNode->isLeafNode() == true){
    bitCodes.push_back(bitCode);
    charHolder.push_back(rootNode->getVal());
    return;
  }
  this->codeGenerator(rootNode->getLeft(), bitCode + "1" );
  this->codeGenerator(rootNode->getRight(),bitCode + "0");
}
//reutnr char code for each char                                                                                                                                                                                                                                                                                                                                            
string HuffTree::getCharCode(int asciiCode){
  for(int i = 0; i < this->getCharVecSize(); i++){
    if((int)asciiCode == (charHolder[i])){
      return bitCodes[i];
    }
  }
  return NULL;
}
//destructor                                                                                                                                                                                                                                                                                                                                                                
HuffTree::~HuffTree(){
  deleteNode(getRoot());
}
