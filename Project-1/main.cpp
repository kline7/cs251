/**                                                                                                                                                                                     
 *  CS251 - Spring 2018: Project 1                                                                                                                                                      
 */

#include <iostream>
#include <stdio.h>
using namespace std;

void printDash(int c);

int main(int argc, char** argv)
{
        /* Use input/output using C++ like notation would use "cin" and "cout" to read/write to stdin/stdout */

    /* ------------------------------- */
    /* process inputs and write output */
    /* ------------------------------- */

  int count =0;
  int c = 1;
  int head;

  cin >> head;
  //printDash()        
  printDash(head);
  int number;
  //while file still has numbers                                                                                                                                                        
  while(cin >> number){
  int real = number;
  if(real < 10){
    //if first number                                                                                                                                                                   
    //write out.. " " << " " << real;                                                                                                                                                   
    if((count + 1) % head == 0){
      cout << " " << " " <<real;
    }
    //if other number                                                                                                                                                                   
    //write out.. " " << " " << real << " " << "|" << " ";                                                                                                                              
    if((count + 1) % head != 0){
      cout << " " << " " << real << " " << "|" << " ";
    }
    count++;
 }else if(real >= 10 && real < 100)
    {
      //if first number                                                                                                                                                                 
      //write out.. " " << real;                                                                                                                                                        
      if((count + 1) % head == 0){
        cout << " " << real;
      }
      //if other number                                                                                                                                                                 
      //write out.. " " << real << " " << "|" << " ";                                                                                                                                   
      if((count + 1) % head !=0){
        cout << " " << real << " " << "|" << " ";
      }
      count++;

    }else
    {
      //if first number                                                                                                                                                                 
      //write out.. real;                                                                                                                                                               
      if((count + 1) % head == 0){
        cout << real;
      }
      //if other number                                                                                                                                                                 
      //write out.. real << " " << "|" << " ";                                                                                                                                          
      if((count + 1) % head != 0){
        cout << real << " " << "|" << " ";
      }
      count++;
    }

  //if end                                                                                                                                                                              
  //write out.. endl;                                                                                                                                                                   
  if(count == head){
    cout << "\r"  <<endl;
    printDash(head);
    count = 0;
  }
 //end while                                                                                                                                                                           
  }
  //printDash()                                                                                                                                                                         
  //printDash(head);                                                                                                                                                                    


    /* Exit the program */
    return 0;
}
void printDash(int c){
  for(int i=0; i < 6 * c - 3; i ++){
    cout << "-";
  }
  cout << "\r"  << endl;
}




