include <iostream>
#include <vector>
#include "Node.h"
#include "RBTree.h"
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

//#define DEBUG x                                                                                                                                                                                                                                                                                                                                                           
using namespace std;

// Input stream operator overload for node elements                                                                                                                                                                                                                                                                                                                         
istream& operator>>(istream& in, vector<pair<string, int>>& e);
//Function to compare two elements                                                                                                                                                                                                                                                                                                                                          
struct sort_pred {
  bool operator()(const std::pair<string,int>  &a,const  std::pair<string,int>  &b)
{

  return (a.second > b.second);
}
};

//Function to sort alphabetically                                                                                                                                                                                                                                                                                                                                           
vector<pair<string,int>> sortAlpha(vector<pair<string,int>>& a)
{
  int size = a.size();
  for(int i = 0;i<size-1;i++)
    {
      if (a.at(i).first > a.at(i+1).first)
        {
          pair<string,int> timp = a.at(i+1);
          a.at(i+1) = a.at(i);
          a.at(i) = timp;
        }
    }
  return a;
}

//Function to find Intersections                                                                                                                                                                                                                                                                                                                                            
vector<pair<string,int>> intersection(vector<pair<string,int>>& finalVec,vector<pair<string,int>>& integrate);
//Function to print out listElements                                                                                                                                                                                                                                                                                                                                        
void printVec(vector<vector<pair<string,int>>> & printMe);
void printLastVec(vector<pair<string,int>> &printMe);
int main(int argc, char** argv) {
        // Implement your search code here                                                                                                                                                                                                                                                                                                                                  
  #ifdef DEBUG
  cout<<"argc"<<argc<<endl;
  #endif
  int numOfWords = argc-2;
  if(argc >2 && argc <=7 )
    {
      #ifdef DEBUG
      cout<<"opening..."<<endl;
      #endif
      ifstream inFile;
      inFile.open(argv[1]);
      if(inFile.fail())
        {
          return 1;
        }
      //create the rbtree to search                                                                                                                                                                                                                                                                                                                                         
      RBTree<string,vector<pair<string,int>>> bigTree ;
      inFile >> bigTree;
      //vector to hold the list of elements                                                                                                                                                                                                                                                                                                                                 
      vector<vector<pair<string,int>>> listElements;
      //Node to insert word elements into element list                                                                                                                                                                                                                                                                                                                      
      Node<string,vector<pair <string,int>>> * nodeBoii;
      for(int i = 1; i<=numOfWords;i++)
        {
          //read in the words from terminal put toLower                                                                                                                                                                                                                                                                                                                     
          string word = argv[i+1];
          transform(word.begin(),word.end(),word.begin(), ::tolower);
          #ifdef DEBUG
          cout<<"word "<<word<<endl;
          #endif
          //search the RBTree to find if it contains word                                                                                                                                                                                                                                                                                                                   
          if(nodeBoii = bigTree.search(word))
            {
              if(nodeBoii){
              #ifdef DEBUG
              cout<<"found word"<<endl;
              #endif
              listElements.push_back(nodeBoii->getElement());
              }
            }
          else
            {
              cout<<"Not found"<<endl;
              return 1;
            }
        }
 //all the urls have been put into the listElements now need to do Intersection and sort                                                                                                                                                                                                                                                                               
      /**************************************************************************************                                                                                                                                                                                                                                                                               
        Intersection takes in two vectors and creates a single vector of the intersection.                                                                                                                                                                                                                                                                                  
        It also includes an int to show how many iterations there are left                                                                                                                                                                                                                                                                                                  
        to create a single intersection vector for all the words                                                                                                                                                                                                                                                                                                            
      ***************************************************************************************/
      //if only one word no need to intersect                                                                                                                                                                                                                                                                                                                               
      if(numOfWords ==1)
        {
         vector<pair<string,int>> sorter = listElements.at(0);
         sorter = sortAlpha(sorter);
         std::sort(sorter.begin(),sorter.end(), sort_pred());
         // sort alpha                                                                                                                                                                                                                                                                                                                                                      
         int end = 0,start = -1;
         for(int i = 0;i<sorter.size()-1;i++)
           {

             if ((i+2 == sorter.size()) && sorter.at(i).second == sorter.at(i+1).second)
               {
                 if(start==-1)
                   {
                     start = i;
                   }
                 if(end==0)
                   {
                     end = sorter.size();
                   }
               }
             if((i+1 != sorter.size()) && (sorter.at(i).second == sorter.at(i+1).second))
               {
                 if(start == -1)
                   {
                     start = i;
                   }
                 if((start!=-1)&&(i+2 != sorter.size())&&(sorter.at(i).second != sorter.at(i+2).second))
                   {
                     end = i+2;
                   }
               }
             if((start != -1)&&(end!=0))
               {
                 // cout<<"start: "<<start<<" end: "<<end<<endl;                                                                                                                                                                                                                                                                                                            
                 sort(sorter.begin()+start,sorter.begin()+end);
                 start = -1;
                 end = 0;
               }

           }
         printLastVec(sorter);

        }
else if(numOfWords == 2)
        {
          vector<pair<string,int>> inter = intersection(listElements.at(0),listElements.at(1));
          inter = sortAlpha(inter);
          std::sort(inter.begin(),inter.end(),sort_pred());
          int end = 0,start = -1;
          for(int i = 0;i<inter.size()-1;i++)
            {

              if ((i+2 == inter.size()) && inter.at(i).second == inter.at(i+1).second)
                {
                  if(start==-1)
                    {
                      start = i;
                    }
                  if(end==0)
                    {
                      end = inter.size();
                    }
                }
              if((i+1 != inter.size()) && (inter.at(i).second == inter.at(i+1).second))
                {
                  if(start == -1)
                    {
                      start = i;
                    }
                  if((start!=-1)&&(i+2 != inter.size())&&(inter.at(i).second != inter.at(i+2).second))
                    {
                      end = i+2;
                    }
                }
              if((start != -1)&&(end!=0))
                {
                  // cout<<"start: "<<start<<" end: "<<end<<endl;                                                                                                                                                                                                                                                                                                           
                  sort(inter.begin()+start,inter.begin()+end);
                  start = -1;
                  end = 0;
                }

            }
          printLastVec(inter);
        }
 else if(numOfWords > 2)
        {
          vector<pair<string,int>> inter = intersection(listElements.at(0),listElements.at(1));
          for(int i =2; i < numOfWords;i++)
            {
              inter = intersection(inter,listElements.at(i));
            }
          inter = sortAlpha(inter);
          std::sort(inter.begin(),inter.end(),sort_pred());
          //sort alpha                                                                                                                                                                                                                                                                                                                                                      
          /*int count = 0;                                                                                                                                                                                                                                                                                                                                                  
          for(int i = 0;i<inter.size()-1;i++)                                                                                                                                                                                                                                                                                                                               
            {                                                                                                                                                                                                                                                                                                                                                               
              int start,end;                                                                                                                                                                                                                                                                                                                                                
              if(inter.at(i).second == inter.at(i+1).second)                                                                                                                                                                                                                                                                                                                
                {                                                                                                                                                                                                                                                                                                                                                           
                  if(count == 0)                                                                                                                                                                                                                                                                                                                                            
                    {                                                                                                                                                                                                                                                                                                                                                       
                      start = i;                                                                                                                                                                                                                                                                                                                                            
                    }                                                                                                                                                                                                                                                                                                                                                       
                  count++;                                                                                                                                                                                                                                                                                                                                                  
                }                                                                                                                                                                                                                                                                                                                                                           
              if(inter.at(i).second != inter.at(i+1).second && count != 0)                                                                                                                                                                                                                                                                                                  
                {                                                                                                                                                                                                                                                                                                                                                           
                  end = i+1;                                                                                                                                                                                                                                                                                                                                                
                  sort(inter.begin()+start, inter.begin()+end);                                                                                                                                                                                                                                                                                                             
                  count = 0;                                                                                                                                                                                                                                                                                                                                                
                }                                                                                                                                                                                                                                                                                                                                                           
                }*/
          int end = 0,start = -1;
          for(int i = 0;i<inter.size()-1;i++)
            {

              if ((i+2 == inter.size()) && inter.at(i).second == inter.at(i+1).second)
                {
                  if(start==-1)
                    {
                      start = i;
                    }
                  if(end==0)
                    {
                      end = inter.size();
                    }
                }
              if((i+1 != inter.size()) && (inter.at(i).second == inter.at(i+1).second))
                {
                  if(start == -1)
                    {
                      start = i;
                    }
                  if((start!=-1)&&(i+2 != inter.size())&&(inter.at(i).second != inter.at(i+2).second))
                    {
                      end = i+2;
                    }
                }
              if((start != -1)&&(end!=0))
                {
                  // cout<<"start: "<<start<<" end: "<<end<<endl;                                                                                                                                                                                                                                                                                                           
                  sort(inter.begin()+start,inter.begin()+end);
                  start = -1;
                  end = 0;
                }

            }
       printLastVec(inter);
        }

    }
  else
    {
      cout<<"Usage: ./search.org RBTree phrase"<<endl<<"Phrase must be between 1 and 5 words"<<endl;
    }


        return 0;
}

//Function to check for Intersections and create the final list                                                                                                                                                                                                                                                                                                             
vector<pair<string,int>> intersection(vector<pair<string,int>>& finalVec,vector<pair<string,int>>& integrate)
{
  int finSize = finalVec.size();
  int inteSize = integrate.size();
  vector<pair<string,int>> ret;
  pair<string,int> putMeIn;
  std::sort(finalVec.begin(),finalVec.end(),sort_pred());
  std::sort(integrate.begin(),integrate.end(),sort_pred());
  for(int i = 0; i < finSize; i++)
    {
      for(int k = 0; k < inteSize; k++)
        {
          if(finalVec.at(i).first.compare(integrate.at(k).first) == 0)
            {
              putMeIn.first = finalVec.at(i).first;
              putMeIn.second = finalVec.at(i).second + integrate.at(k).second;
              ret.push_back(putMeIn);
            }
        }
    }
  return ret;
}

  //Function to print the vector                                                                                                                                                                                                                                                                                                                                            
  void printLastVec(vector<pair<string,int>> &printMe)
  {
    int sizeOfList = printMe.size();
    #ifdef DEBUG
    cout<<"size: "<<sizeOfList<<endl;
    #endif
    for(int i = 0; i<sizeOfList;i++)
      {
        cout<<printMe.at(i).first<<" "<<printMe.at(i).second<<endl;
      }

      }


// This function overloads the input stream operator for Node                                                                                                                                                                                                                                                                                                               
// elements. It has been provided to you and does not need to be                                                                                                                                                                                                                                                                                                            
// altered.                                                                                                                                                                                                                                                                                                                                                                 
istream& operator>>(istream& in, vector<pair<string, int>>& e) {
        // Clear any existing contents                                                                                                                                                                                                                                                                                                                                      
        e.clear();

        // Read the number of elements                                                                                                                                                                                                                                                                                                                                      
        size_t n;
        in >> n;
        for (int i = 0; i < n; i++) {
                // Read each member of each pair the vector stores                                                                                                                                                                                                                                                                                                          
                string u;
                in >> u;
                int f;
                in >> f;
                // Add to vector                                                                                                                                                                                                                                                                                                                                            
                e.push_back(make_pair(u, f));
        }

        return in;
}
