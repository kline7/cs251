#include <iostream>

using namespace std;

void enternumber(long[], int);

int main()
{
  
  int size;//var to hold the size of the freq table
  int numbers5=0;//var to hold how many numbers have a freq of 5

  cout << "How many numbers?  ";//print out to get size of table
  cin >>size;//read in input on the size and put it in size

  long enteredNumbers[10000];//initialize enterednumbers array
  long frequencyArray[10000];//initialize freq table array

  enternumber(enteredNumbers,size);//call enternumb func passing entnumbers array and size
  //for loop to fill up the freq table
  for (int x=0; x<size; x++)
  {
    if (enteredNumbers[x]  == enteredNumbers[x] )
    {
      frequencyArray[enteredNumbers[x]]++;
    }
  }

  for (int z=0; z<size; z++)
  {
    cout<<frequencyArray[z];
    if (frequencyArray[z]==5)
    {
      numbers5++;
    }
  }
  cout << "The number of values that show up 5  times is " << numbers5;
}

void enternumber(long enteredNumbers[],int f)
{
  for ( int count=0; count<f; count++)
  {
    cout << "Enter an Integer:  ";
    cin >> enteredNumbers[count];
  }
}
