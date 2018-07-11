#include <stdio.h>
#include <sstream>
#include <iostream>
#include "Node.h"
#include "RBTree.h"
#include "SimpleHTMLParser.h"
#include <vector>
#include <string>
#include <fstream>
#define show(x,y) cout<<x<<" "<<y<<endl
//#define DEBUG x                                                                                                                                                                                                                                                                                                                                                           
using namespace std;
// Output stream operator overload for node elements                                                                                                                                                                                                                                                                                                                        
ostream& operator<<(ostream& out, const vector<pair<string, int>>& e);
     int newNode = 0;
//Function to traverse the vector for a match                                                                                                                                                                                                                                                                                                                               
int find(vector<pair<string,int>> vec, string url)
{
  int found = -1;
  if(url.empty())
    return found;
  pair<string,int> iter;
  for(int i=0;i<vec.size();i++)
    {
      iter = vec.at(i);
      if(iter.first.compare(url) == 0)
        {
          found = i;
        break;
        }
    }
  return found;
}
//Function to create and populate vector for new node                                                                                                                                                                                                                                                                                                                       
vector<pair<string,int>> createVec(string url)
{
  vector<pair<string,int>> element;
  pair<string,int> data;
  data.first = url;
  data.second = 1;
  element.insert(element.begin(),data);
  return element;
}
int thing = 0;
//Function to put the words intot the rb tree returns rb tree                                                                                                                                                                                                                                                                                                               
RBTree<string,vector<pair<string,int>>>  putInWords(string url , vector<string> words ,RBTree<string,vector<pair<string,int>>> rbt)
{
  /********************************************************                                                                                                                                                                                                                                                                                                                 
   *Key: Word                                                                                                                                                                                                                                                                                                                                                               
   *Element: list of 'urls' with 'fregquency' of that word                                                                                                                                                                                                                                                                                                                  
  *********************************************************/

  //cout<<"size: "<<words.size()<<endl;                                                                                                                                                                                                                                                                                                                                     
  int length = words.size();
  string word;
  Node<string,vector<pair<string,int>>> * node;
  pair<string,int> data;
  for(int i = 0;i<length;i++)
    {
      //cout<<words.at(i)<<" : "<<i<<endl;                                                                                                                                                                                                                                                                                                                                  
     node = rbt.search(words.at(i));
     if(!node)
       {
         vector<pair<string,int>> element;
         element = createVec(url);
         rbt.insert(words.at(i),element);
         newNode++;
       }
     else{
       //cout<<"return customer"<<endl;                                                                                                                                                                                                                                                                                                                                     
       vector<pair<string,int>> element = node->getElement();
       int index = -1;

       if ((find(element,url)) != -1)
         {
          //found element                                                                                                                                                                                                                                                                                                                                                   
           index = find(element,url);
           //if(node->getKey().compare("the")==0)                                                                                                                                                                                                                                                                                                                           
             #ifdef DEBUG
             cout<<node->getKey()<<index<<" : "<<url<<" : "<<element.at(index).first<<endl;
             #endif
           data = element.at(index);
           #ifdef DEBUG
           cout<<thing++<<endl;
           #endif
           data.second++;
           element[index] = data;
           node->setElement(element);
         }
       else{
         //element not found                                                                                                                                                                                                                                                                                                                                                
         data.first = url;
         data.second = 1;
         element.push_back(data);
         node->setElement(element);
         }
     }

    }
  return rbt;
}
//Function to take text string and split it into vector returns vector                                                                                                                                                                                                                                                                                                      
vector<string>  splitText(string text)
{
  unsigned i = 0;
  vector<string> tok;
  istringstream iss(text);
  string word,space =" ",feed="\f";
  while(getline(iss,word,' '))
    {

      if(word.compare(space)!=0 && !word.empty() && !(word.compare(feed) ==0&&(word.size()==1))){
        //cout<<"push_back:"<<word<<" : "<<i;                                                                                                                                                                                                                                                                                                                               
        tok.insert(tok.begin()+i,word);
        //cout<<" : "<<tok[i]<<" : "<<tok.at(i)<<endl;                                                                                                                                                                                                                                                                                                                      
        i++;
      }
    }
  return tok;
}
int main(int argc, char** argv) {
        // Implement your scan code here                                                                                                                                                                                                                                                                                                                                    
  //argv1 is in argv2 is out                                                                                                                                                                                                                                                                                                                                                
  //Node<string,vector<pair<string,int>>> * node;                                                                                                                                                                                                                                                                                                                           
  if (argc == 3)
    {
      RBTree<string,vector<pair<string,int>>> bigTree ;
      SimpleHTMLParser * html = new SimpleHTMLParser();
      // cout<<"opening file..."<<endl;                                                                                                                                                                                                                                                                                                                                     
      ifstream inFile;
      inFile.open(argv[1]);
      if(inFile.fail()){
        return 1;
      }
      //cout<<"reading..."<<endl;                                                                                                                                                                                                                                                                                                                                           
      //reading in the urls                                                                                                                                                                                                                                                                                                                                                 
        int length;//how many urls are in the list                                                                                                                                                                                                                                                                                                                          
        inFile >> length;
        //cout<<"legnth "<<length<<endl;                                                                                                                                                                                                                                                                                                                                    
        string url,urlText;
        bool error = 0;
        vector<string> tokens;
        for(int i = 1; i<=length;i++)
          {
            inFile >> url;
            //cout<<url<<endl;                                                                                                                                                                                                                                                                                                                                              
            //      show(url,i);                                                                                                                                                                                                                                                                                                                                            
            //cout<<" Parsing..";                                                                                                                                                                                                                                                                                                                                           
            error = html->parse(url);
            //cout<<" error?: "<<error<<endl;                                                                                                                                                                                                                                                                                                                               
            if (error==1){
            urlText = html->getText();
            //cout<<"urlText: "<<urlText<<endl;                                                                                                                                                                                                                                                                                                                             
            tokens = splitText(urlText);
            bigTree = putInWords(url,tokens,bigTree);
            }
            ofstream outFile;
            outFile.open(argv[2]);
            if(outFile.fail()){
              return 1;
            }
            outFile<<newNode<<endl;
            bigTree.inorder(outFile);
            outFile<<endl;
            //outFile<< bigTree.getRoot();                                                                                                                                                                                                                                                                                                                                  
          }




    }
  else{
    cout<<"Usage: ./scan.org inputfile outputfile"<<endl;
  }

        return 0;
}

// This function overloads the output stream operator for Node                                                                                                                                                                                                                                                                                                              
// elements. It has been provided to you and does not need to be                                                                                                                                                                                                                                                                                                            
// altered.                                                                                                                                                                                                                                                                                                                                                                 
ostream& operator<<(ostream& out, const vector<pair<string, int>>& e) {
        // Write the number of elements in the vector                                                                                                                                                                                                                                                                                                                       
        out << e.size() << endl;
        for (auto& uf : e)
                // Write each member of each pair the vector stores                                                                                                                                                                                                                                                                                                         
                out << uf.first << " " << uf.second << endl;
        return out;
}

