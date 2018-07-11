#include<iostream>
#include <stdio.h>
#include <string>
#include "mystack.h"

using namespace std;

int main(){
  std::string type;
  std::string command;
  cin >> type;
  if(type.compare("int") == 0)
    {
      mystack<int> stackInt;
      int x;
      while(cin>> command){
        if(command.compare("push") == 0){
          cin >> x;
          stackInt.push(x);
        }else if(command.compare("pop") == 0){
          if(!stackInt.empty()){
          int retPop = -1;
          retPop = stackInt.pop();
          cout << retPop << endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("top") == 0){
          if(!stackInt.empty()){
          int retTop = -1;
          retTop = stackInt.top();
          cout << retTop <<endl;
          }else{
          cout << "error"<<endl;
          }
        }else if(command.compare("empty") == 0){
          bool retEmpty;
          retEmpty = stackInt.empty();
          cout << retEmpty << endl;
        }else if(command.compare("size") == 0){
          int retSize = 0;
          retSize = stackInt.size();
          cout << retSize << endl;
        }
      }
      cout << endl;
    }else if(type.compare("double") == 0)
    {
      //implement same as before                                                                                                                                                                                                                                                                                                                                            
      mystack<double> stackDouble;
      double x;
      while(cin>> command){
        if(command.compare("push") == 0){
          cin >> x;
          stackDouble.push(x);
        }else if(command.compare("pop") == 0){
          if(!stackDouble.empty()){
          double retPop = -1;
          retPop = stackDouble.pop();
          cout << retPop << endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("top") == 0){
          if(!stackDouble.empty()){
          double retTop = -1;
          retTop = stackDouble.top();
          cout << retTop <<endl;
          }else{
          cout << "error"<<endl;
          }
       }else if(command.compare("empty") == 0){
          bool retEmpty;
          retEmpty = stackDouble.empty();
          cout << retEmpty << endl;
        }else if(command.compare("size") == 0){
          int retSize = 0;
          retSize = stackDouble.size();
          cout << retSize << endl;
        }
      }
      cout<<endl;
    }else if(type.compare("char") == 0)
    {
 //implement same as before                                                                                                                                                                                                                                                                                                                                            
      mystack<double> stackDouble;
      double x;
      while(cin>> command){
        if(command.compare("push") == 0){
          cin >> x;
          stackDouble.push(x);
        }else if(command.compare("pop") == 0){
          if(!stackDouble.empty()){
          double retPop = -1;
          retPop = stackDouble.pop();
          cout << retPop << endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("top") == 0){
          if(!stackDouble.empty()){
          double retTop = -1;
          retTop = stackDouble.top();
          cout << retTop <<endl;
          }else{
          cout << "error"<<endl;
          }
       }else if(command.compare("empty") == 0){
          bool retEmpty;
          retEmpty = stackDouble.empty();
          cout << retEmpty << endl;
        }else if(command.compare("size") == 0){
          int retSize = 0;
          retSize = stackDouble.size();
          cout << retSize << endl;
        }
      }
      cout<<endl;
       }else if(type.compare("char") == 0)
    {
      //implement same as before                                                                                                                                                                                                                                                                                                                                            
      mystack<char> stackChar;
      char x;
      while(cin>> command){
        if(command.compare("push") == 0){
          cin >> x;
          stackChar.push(x);
        }else if(command.compare("pop") == 0){
          if(!stackChar.empty()){
          char retPop = -1;
          retPop = stackChar.pop();
          cout << retPop << endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("top") == 0){
          if(!stackChar.empty()){
          char retTop = -1;
          retTop = stackChar.top();
          cout << retTop <<endl;
          }else{
          cout << "error"<<endl;
          }
        }else if(command.compare("empty") == 0){
          bool retEmpty;
          retEmpty = stackChar.empty();
          cout << retEmpty << endl;
        }else if(command.compare("size") == 0){
          int retSize = 0;
          retSize = stackChar.size();
          cout << retSize << endl;
        }
      }
      cout<<endl;

    }else if(type.compare("string") == 0)
    {
//implement same as before                                                                                                                                                                                                                                                                                                                                            
      mystack<std::string> stackStr;
      std::string  x;
      while(cin>> command){
        if(command.compare("push") == 0){
          cin >> x;
          stackStr.push(x);
        }else if(command.compare("pop") == 0){
          if(!stackStr.empty()){
          std::string  retPop;
          retPop = stackStr.pop();
          cout << retPop << endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("top") == 0){
          if(!stackStr.empty()){
          std::string retTop ;
          retTop = stackStr.top();
          cout << retTop <<endl;
          }else{
          cout << "error"<<endl;
          }
        }else if(command.compare("empty") == 0){
          bool retEmpty;
          retEmpty = stackStr.empty();
          cout << retEmpty << endl;
        }else if(command.compare("size") == 0){
          int retSize = 0;
          retSize = stackStr.size();
          cout << retSize << endl;
        }
      }
      cout<<endl;
    }

        return 0;
}
