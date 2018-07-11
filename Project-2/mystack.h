#ifndef MYSTACK_H
#define MYSTACK_H
#define MAX_SIZE 10000
#include <iostream>


using namespace std;
template <class T>
class mystack{
  private:
        // Declare necessary variables and methods                                                                                                                                                                                                                                                                                                                          
  int TOP;
  T Data[MAX_SIZE];
  public:

        mystack();
        void push(T x);
        T top();
        T pop();
        bool empty();
        int size();
};

//------------------------------------------------------                                                                                                                                                                                                                                                                                                                    
//implementation of stack                                                                                                                                                                                                                                                                                                                                                   
//------------------------------------------------------                                                                                                                                                                                                                                                                                                                    





template < class T>
mystack<T>::mystack(){
  TOP = -1;
}

template < class T >
void mystack<T>::push(T x){
  //if not full                                                                                                                                                                                                                                                                                                                                                             
  if(TOP<MAX_SIZE){
    TOP += 1;
    Data[TOP] = x;
  }
  //if(TOP>MAX_SIZE)                                                                                                                                                                                                                                                                                                                                                        
  //cout<<"ERROR:Stack is full"<<endl;                                                                                                                                                                                                                                                                                                                                      
}

template < class T >
T mystack<T>::top(){
  //dont check for error                                                                                                                                                                                                                                                                                                                                                    
  //if(!this->empty()){                                                                                                                                                                                                                                                                                                                                                     
    return Data[TOP];
    //}                                                                                                                                                                                                                                                                                                                                                                     
  // cerr << "Stack is Empty";                                                                                                                                                                                                                                                                                                                                              


}

template < class T >
T mystack<T>::pop(){
  T val;
  //dont check for error in here do it in the main                                                                                                                                                                                                                                                                                                                          
  //if(!mystack<T>::empty()){                                                                                                                                                                                                                                                                                                                                               
    val = Data[TOP];
    TOP -= 1;

    //}else                                                                                                                                                                                                                                                                                                                                                                 
    //{                                                                                                                                                                                                                                                                                                                                                                     
    //cerr<< "Stack is Empty";                                                                                                                                                                                                                                                                                                                                              
    //}                                                                                                                                                                                                                                                                                                                                                                     
  return val;

}

template < class T >
bool  mystack<T>::empty(){
  if(TOP == -1)//is empty                                                                                                                                                                                                                                                                                                                                                   
    return 1;
  else
    return 0;//not empty                                                                                                                                                                                                                                                                                                                                                    
}

template < class T>
int mystack<T>::size(){
  if(TOP == -1){
    return 0;
  }else
    {
      return TOP+1;
    }
}



#endif
