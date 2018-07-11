#include <iostream>
#include <string>
#include <stdio.h>
#include "myqueue.h"
using namespace std;
/*                                                                                                                                                                                                                                                                                                                                                                          
all implementation needs to be moved to the myqueue.h file                                                                                                                                                                                                                                                                                                                  
                                                                                                                                                                                                                                                                                                                                                                            
all that should be in this is the main method to read/write to file                                                                                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                                                                                                                            
 */

bool error = false;
template < class T>
myqueue<T>::myqueue()
{
  Data = new T[MAX_SIZE];
}
  int begin = 0;
  int end = 0;
  int elemCount = 0;


template < class T >
void myqueue<T>::enqueue(T x){
  if(elemCount < MAX_SIZE){
    Data[end++ ] = x;
    ++elemCount;
    //wrap around                                                                                                                                                                                                                                                                                                                                                           
    if(end > MAX_SIZE){
      end -= (MAX_SIZE +1);
    }
  }
  //if(elemCount >= MAX_SIZE)                                                                                                                                                                                                                                                                                                                                               
  //error=true;cout << "error"<<endl;                                                                                                                                                                                                                                                                                                                                       
}

template< class T>
T myqueue<T>::dequeue(){
  error = false;
  if(elemCount > 0){
    T val = Data[begin++ ];
    elemCount--;
    //wrap around                                                                                                                                                                                                                                                                                                                                                           
    if(begin > MAX_SIZE){
      begin -= (MAX_SIZE + 1);
    }
    return val;
  }
  //cout << "error"<<endl;                                                                                                                                                                                                                                                                                                                                                  
  error = true;
  return 0;
}

template< class T>
int myqueue<T>::size(){
  return elemCount;
}

template<class T>
bool myqueue<T>::empty(){

  if(elemCount > 0){
    return 0;
  }
  return 1;
}

template<class T>
T myqueue<T>::front(){
  error = false;
  if(!myqueue<T>::empty()){
    return Data[begin];
  }
  //cout << "error"<<endl;                                                                                                                                                                                                                                                                                                                                                  
  error = true;
  return 0;


}

int main(){


  std:: string type;
  std::string command;

  cin >> type;

  if(type.compare("int") == 0){
    myqueue<int> queueInt;
    int x;
    while(cin >> command){

      if(command.compare("enqueue") == 0){
        cin >> x;
        queueInt.enqueue(x);
      }else if(command.compare("dequeue") == 0){
        if(!queueInt.empty()){
        int retDQ = -1;
        retDQ = queueInt.dequeue();
        cout<<retDQ<<endl;
        }else{
          cout<<"error"<<endl;
        }

      }else if(command.compare("front") == 0){
        if(!queueInt.empty()){
        int retFront = -1;
        retFront = queueInt.front();
        cout<<retFront<<endl;
        }else{
          cout<<"error"<<endl;
        }
      }else if(command.compare("empty") == 0){
        bool retEmpty;
        retEmpty = queueInt.empty();
        cout<<retEmpty<<endl;
      }else if(command.compare("size") == 0){
        int retSize = 0;
        retSize = queueInt.size();
        cout<<retSize<<endl;
      }
    }
    cout << endl;
  }else if(type.compare("double") == 0){
    myqueue<double> queueDouble;
    double x;
    while(cin >> command){
      if(command.compare("enqueue") == 0){
        cin >> x;
        queueDouble.enqueue(x);
      }else if(command.compare("dequeue") == 0){
        if(!queueDouble.empty()){
        double retDQ = -1;
        retDQ = queueDouble.dequeue();
        cout<<retDQ<<endl;
        }else{
          cout<<"error"<<endl;
        }
   }else if(command.compare("front") == 0){
        if(!queueDouble.empty()){
        double retFront = -1;
        retFront = queueDouble.front();
        cout<<retFront<<endl;
        }else{
          cout<<"error"<<endl;
        }
      }else if(command.compare("empty") == 0){
        bool retEmpty;
        retEmpty = queueDouble.empty();
        cout<<retEmpty<<endl;
      }else if(command.compare("size") == 0){
        int retSize = 0;
        retSize = queueDouble.size();
        cout<<retSize<<endl;
           }
         }
    cout<<endl;
}else if(type.compare("char") == 0){
      myqueue<char> queueChar;
      char x;
      while(cin >> command){
        if(command.compare("enqueue") == 0){
          cin >> x;
          queueChar.enqueue(x);
        }else if(command.compare("dequeue") == 0){
          if(!queueChar.empty()){
          char retDQ ;
          retDQ = queueChar.dequeue();
          cout<<retDQ<<endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("front") == 0){
          if(!queueChar.empty()){
          char retFront ;
          retFront = queueChar.front();
          cout<<retFront<<endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("empty") == 0){
          bool retEmpty;
          retEmpty = queueChar.empty();
          cout<<retEmpty<<endl;
        }else if(command.compare("size") == 0){
          int retSize = 0;
          retSize = queueChar.size();
          cout<<retSize<<endl;
        }
      }
      cout<<endl;
    }else if(type.compare("string") == 0){
      myqueue<std::string> queueStr;
      std::string x;
      while(cin >> command){
        if(command.compare("enqueue") == 0){
          cin >> x;
          queueStr.enqueue(x);
        }else if(command.compare("dequeue") == 0){
          if(!queueStr.empty()){
          std::string retDQ ;
          retDQ = queueStr.dequeue();
          cout<<retDQ<<endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("front") == 0){
          if(!queueStr.empty()){
          std::string  retFront;
          retFront = queueStr.front();
          cout<<retFront<<endl;
          }else{
            cout<<"error"<<endl;
          }
        }else if(command.compare("empty") == 0){
          bool retEmpty;
          retEmpty = queueStr.empty();
          cout<<retEmpty<<endl;
        }else if(command.compare("size") == 0){
          int retSize = 0;
          retSize = queueStr.size();
          cout<<retSize<<endl;
        }
      }
      cout<<endl;

    }
  return 0;
}
