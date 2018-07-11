ifndef PROJ4_RBTREE_H
#define PROJ4_RBTREE_H
#include <queue>
#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <assert.h>
#include <stdlib.h>
using namespace std;

template <typename Key, typename Element>
class RBTree {
 private:
  size_t tSize;
  Node<Key,Element>* root;
  void rotateLeft(Node<Key,Element> *);
  void rotateRight(Node<Key,Element> *);
  void Dump(Node<Key,Element> *,int);
  Node<Key,Element> * min(Node<Key,Element> *);
  void delfix(Node<Key,Element> *,const Key& value);
  //attempt at the unreal del                                                                                                                                                                                                                                                                                                                                               
  void RestoreReducedHeight(Node<Key,Element> *);
  public:
  void Dump();
  void inorderHelp(Node<Key,Element> *,ostream& out);
  void levelOrderHelp(Node<Key,Element> *,ostream& out);
  // Implement each of these methods                                                                                                                                                                                                                                                                                                                                        
  RBTree() { tSize = 0; root = NULL;  }
    void insert(const Key& k, const Element& e);
    Node<Key, Element>* search(const Key& k);
    void del(const Key& k);
    void inorder(ostream& out);
    void levelOrder(ostream& out) ;
        size_t size() const;
        Node<Key, Element>* getRoot();
};
//functions to print                                                                                                                                                                                                                                                                                                                                                        
template <typename Key, typename Element>
void RBTree<Key, Element>::Dump()
{
  Dump(root, 0);
}
template <typename Key, typename Element>
void RBTree<Key, Element>::Dump(Node<Key,Element> *node, int tabs)
{
  if(!node)
    {
      return;
    }
  Dump(node->getLeft(), tabs + 1);
  for(int i = 0; i < tabs; ++i)
    {
      cout<< "\t\t";
    }
  cout<< node->getKey() << (node->getColor() ? "B" : "R") << endl;
  Dump(node->getRight(), tabs + 1);
}
// Function to insert a new node with given data                                                                                                                                                                                                                                                                                                                            
template <typename Key, typename Element>
void RBTree<Key, Element>::insert(const Key& key, const Element& element)
{
  Node<Key,Element> *node, *parent, *z;
  parent = NULL;
  node = root;
  while(node)
    {
      parent = node;
      if(key < node->getKey())
        {
          node = node->getLeft();
        }
      else
        {
          node = node->getRight();
        }
    }

  if(!parent)
    {
      z = root = new Node<Key,Element>;
      z->setKey(key);
      z->setElement(element);
      z->setColor(BLACK);
      z->setParent(NULL);
      z->setLeft(NULL);
      z->setRight(NULL);
    }
    else
    {
      z = new Node<Key, Element>;
      z->setKey(key);
      z->setElement(element);
      z->setColor(RED);
      z->setParent(parent);
      z->setLeft(NULL);
      z->setRight(NULL);
      if(z->getKey() < parent->getKey())
        {
          parent->setLeft(z);
        }
      else
        {
          parent->setRight(z);
        }
    }
  Node<Key,Element> * uncle;
  bool side;
  while (z->getParent() && z->getParent()->getColor() == RED)
    {
      if((side = (z->getParent() == z->getParent()->getParent()->getLeft())))
        {
          uncle = z->getParent()->getParent()->getRight();
        }
      else
        {
          uncle = z->getParent()->getParent()->getLeft();
        }

      if (uncle && uncle->getColor() == RED)
        {
          z->getParent()->setColor(BLACK);
          uncle->setColor(BLACK);
          z->getParent()->getParent()->setColor(RED);
          z = z->getParent()->getParent();
        }
      else
        {
          if( z == (side ? z->getParent()->getRight() : z->getParent()->getLeft()))
            {
              z = z->getParent();
              side ? rotateLeft(z) : rotateRight(z);
            }
          z->getParent()->setColor(BLACK);
          z->getParent()->getParent()->setColor(RED);
          side ? rotateRight(z->getParent()->getParent()) : rotateLeft(z->getParent()->getParent());
        }
    }
  root->setColor(BLACK);
  tSize++;
}
//Function to rotate left                                                                                                                                                                                                                                                                                                                                                   
template <typename Key, typename Element>
void RBTree<Key, Element>::rotateLeft(Node<Key,Element> *x)
{
  Node<Key, Element> *y;

  y = x->getRight();
  x->setRight(y->getLeft());
  if(y->getLeft())
    {
      y->getLeft()->setParent(x);
    }
  y->setParent(x->getParent());
  y->setLeft(x);

  if (!x->getParent())
    {
      root = y;
    }
  else if (x == x->getParent()->getLeft())
    {
      x->getParent()->setLeft(y);
    }
  else
    {
      x->getParent()->setRight(y);
    }
  x->setParent(y);
}
//Function to rotate right                                                                                                                                                                                                                                                                                                                                                  
template <typename Key, typename Element>
void RBTree<Key, Element>::rotateRight(Node<Key,Element> *y)
{
  Node<Key,Element> *x;
  x = y->getLeft();
  y->setLeft(x->getRight());
  if (x->getRight())
    {
      x->getRight()->setParent(y);
    }
  x->setParent(y->getParent());
  x->setRight(y);

  if (!y->getParent())
    {
      root = x;
    }
  else if ( y == y->getParent()->getLeft())
    {
      y->getParent()->setLeft(x);
    }
  else
    {
      y->getParent()->setRight(x);
    }
  y->setParent(x);

}

// Function to search a node with given data                                                                                                                                                                                                                                                                                                                                
template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::search(const Key& k)
{
  Node<Key,Element> *node = root;
  while(node)
    {
      if (node->getKey() > k)
        {
          node = node->getLeft();
        }
      else if (node->getKey() < k)
        {
          node = node->getRight();
        }
      else
        {
          return node;
        }
    }
  return NULL;
}
// Function to delete a node with given data                                                                                                                                                                                                                                                                                                                                
template <typename Key, typename Element>
void RBTree<Key, Element>::del(const Key& k)
{
  delfix(this->root,k);

  tSize--;//size needs to be decremented                                                                                                                                                                                                                                                                                                                                    
}
//Function helper for del                                                                                                                                                                                                                                                                                                                                                   
template <typename Key, typename Element>
  void RBTree<Key, Element>::delfix(Node<Key, Element> * root,const Key&value)
{
  if(root->getKey() == value)
    {
      Node<Key,Element> *leftmostFromRight;
      if (root->getLeft() == NULL) leftmostFromRight = root->getRight();
      else if (root->getRight() == NULL) leftmostFromRight = root->getLeft();
      else if (root->getLeft()->getRight() == NULL) leftmostFromRight = root->getLeft();
      else if (root->getRight()->getLeft() == NULL) leftmostFromRight = root->getRight();
      //symmetrical after the four exceptional cases above - left implemented                                                                                                                                                                                                                                                                                               
      else
        {
          leftmostFromRight = root->getRight()->getLeft();
          while (leftmostFromRight->getLeft() != NULL)
            {
              leftmostFromRight = leftmostFromRight->getLeft();
            }
        }
      if (leftmostFromRight == NULL)
        {
          //reballance by checking for red-black tree deletion preliminaries in both cases                                                                                                                                                                                                                                                                                  
          if (root->getLeft() != NULL) root->getLeft()->Recolor();
          else if (root->getRight() != NULL) root->getRight()->Recolor();
          //this case is possible only if (leftmostFromRight != root->GetLeft() && root->GetLeft() != NULL)                                                                                                                                                                                                                                                                 
          else if (root->getColor() == BLACK) RestoreReducedHeight(root);
        }
      else
        {
          //leftmostFromRight is always black and its single child is always red - first condition is possible bacause of the four exceptional cases                                                                                                                                                                                                                        
          if (leftmostFromRight->getLeft() != NULL) leftmostFromRight->getLeft()->Recolor();
          else if (leftmostFromRight->getRight() != NULL) leftmostFromRight->getRight()->Recolor();
          //this case is possible only if (leftmostFromRight != root->GetLeft() && root->GetLeft() != NULL)                                                                                                                                                                                                                                                                 
          else if (leftmostFromRight->getColor() == BLACK) RestoreReducedHeight(leftmostFromRight);
          if (leftmostFromRight != root->getLeft() && leftmostFromRight != root->getRight()) leftmostFromRight->getParent()->setLeft(leftmostFromRight->getRight());

          //replace with originally removed node                                                                                                                                                                                                                                                                                                                            
          //include the above cases where leftmost is child of the root                                                                                                                                                                                                                                                                                                     
          if (leftmostFromRight != root->getLeft() && root->getLeft() != NULL) leftmostFromRight->setLeft(root->getLeft());
          if (leftmostFromRight != root->getRight() && root->getRight() != NULL) leftmostFromRight->setRight(root->getRight());
          //recolor if necessary                                                                                                                                                                                                                                                                                                                                            
          if (root->getColor() == RED && leftmostFromRight->getColor() == BLACK) leftmostFromRight->Recolor();
          if (root->getColor() == BLACK && leftmostFromRight->getColor() == RED) leftmostFromRight->Recolor();
        }
      if (root->getParent() != NULL)
        {
          if (root->getParent()->getLeft() == root) root->getParent()->setLeft(leftmostFromRight);
          else root->getParent()->setRight(leftmostFromRight);
        }
      else
        {
          this->root = leftmostFromRight;
          if (this->root != NULL) this->root->setParent(NULL);
        }
      delete root;
    }
  else if(root->getKey() > value)
    {
      if(root->getLeft() == NULL)
        {
          //skip                                                                                                                                                                                                                                                                                                                                                            
        }
      else
        {
          this->delfix(root->getLeft(), value);
        }
    }
  else
    {
  if(root->getRight() == NULL)
        {
          //skip                                                                                                                                                                                                                                                                                                                                                            
        }
      else
        {
          this->delfix(root->getRight(), value);
        }
    }
}
//Function for del                                                                                                                                                                                                                                                                                                                                                          

// Function to do inorder traversal                                                                                                                                                                                                                                                                                                                                         
template <typename Key, typename Element>
void RBTree<Key, Element>::inorder(ostream& out)
{
  if (root == NULL)
    {
      return;
    }
  // Node<Key, Element> * node = this->root;                                                                                                                                                                                                                                                                                                                                
  inorderHelp(this->root,out);
}
template <typename Key, typename Element>
  void RBTree<Key, Element>::inorderHelp(Node<Key,Element> * root, ostream& out)
{
  if (root == NULL)
    {
      return;
    }
  inorderHelp(root->getLeft(),out);
   out<<* root<<endl;
  inorderHelp(root->getRight(),out);

}
// Function to perform level-order traversal                                                                                                                                                                                                                                                                                                                                
template <typename Key, typename Element>
void RBTree<Key, Element>::levelOrder(ostream& out)
{
  if (root == NULL)
    {
      return;
    }
  levelOrderHelp(this->root,out);
}
template <typename Key, typename Element>
  void RBTree<Key, Element>::levelOrderHelp(Node<Key,Element> * root,ostream& out)
{
  if (root == NULL)
    {
      return;
    }
  queue<Node<Key,Element> *> q;
  q.push(root);

  while (!q.empty())
    {
      Node<Key,Element> * temp = q.front();
      out << * temp << endl;
      q.pop();
      if(temp->getLeft() != NULL)
        q.push(temp->getLeft());

      if(temp->getRight() != NULL)
        q.push(temp->getRight());
    }
}
// Function to return the number of nodes in the RBTree                                                                                                                                                                                                                                                                                                                     
template <typename Key, typename Element>
size_t RBTree<Key, Element>::size() const { return tSize; }

// Function to return a pointer to the root of the RBTree                                                                                                                                                                                                                                                                                                                   
template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::getRoot() { return this->root; }
//Function to obtain min node                                                                                                                                                                                                                                                                                                                                               
template <typename Key, typename Element>
Node<Key, Element>* RBTree<Key, Element>::min(Node<Key, Element>* n)
{
  Node<Key,Element> * min = n;
  while(min->getLeft() != NULL)
    {
      min = min->getLeft();
    }
  return min;
}
// The following functions have been provided for you, and do not                                                                                                                                                                                                                                                                                                           
// need to be modified:                                                                                                                                                                                                                                                                                                                                                     


// Output stream operator overload -- writes the contents of the                                                                                                                                                                                                                                                                                                            
// entire RBTree to the specified output stream, using an in-order                                                                                                                                                                                                                                                                                                          
// traversal. Note that there must be a similar operator overload                                                                                                                                                                                                                                                                                                           
// for Key and Element types in order for this to compile.                                                                                                                                                                                                                                                                                                                  
// Example usage:                                                                                                                                                                                                                                                                                                                                                           
//              RBTree<K,E> rbt;                                                                                                                                                                                                                                                                                                                                            
//              cout << rbt << endl;                                                                                                                                                                                                                                                                                                                                        
template <typename Key, typename Element>
ostream& operator<<(ostream& out, const RBTree<Key, Element>& rbtree) {
        out << rbtree.size() << endl;
        rbtree.inorder(out);
        return out;
}

// Input stream operator overload -- reads the contents of an RBTree                                                                                                                                                                                                                                                                                                        
// from the specified input stream, inserting each Node as it is                                                                                                                                                                                                                                                                                                            
// read. Note that there must be a similar operator overload for Key                                                                                                                                                                                                                                                                                                        
// and Element types in order for this to compile.                                                                                                                                                                                                                                                                                                                          
// Example usage:                                                                                                                                                                                                                                                                                                                                                           
//              RBTree<K,E> rbt;                                                                                                                                                                                                                                                                                                                                            
//              cin >> rbt;                                                                                                                                                                                                                                                                                                                                                 
template <typename Key, typename Element>
istream& operator>>(istream& in, RBTree<Key, Element>& rbtree) {
        // Clear existing contents, if any                                                                                                                                                                                                                                                                                                                                  
        rbtree = RBTree<Key, Element>();

        // Read in the number of elements to read                                                                                                                                                                                                                                                                                                                           
        size_t size;
        in >> size;
        for (size_t i = 0; i < size; i++) {
                // Read in each node as it appears in the stream                                                                                                                                                                                                                                                                                                            
                Node<Key, Element> n;
                in >> n;
                // Insert the node into the RBTree                                                                                                                                                                                                                                                                                                                          
                rbtree.insert(n.getKey(), n.getElement());
        }

        return in;
}
