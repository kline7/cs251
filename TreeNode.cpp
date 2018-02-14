#include <iostream>
#include "TreeNode.h"

#include <string>


TreeNode::TreeNode(unsigned char val, unsigned frequency)
{
  this->val = val;
  this->frequency = frequency;
  this->left = NULL;
  this->right = NULL;
}

unsigned TreeNode::getFrequency()
{
        return frequency;
}
unsigned TreeNode::getVal()
{
        return val;
}

TreeNode * TreeNode::getLeft()
{
  return left;
}
TreeNode * TreeNode::getRight()
{
  return right;
}
bool TreeNode::isLeafNode()
{
  return (left == NULL && right == NULL);
}

