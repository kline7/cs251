#include <iostream>

using namespace std;

void enternumber(long[], int);

int main()
{
  int size;
  int numbers5=0;

  cout << "How many numbers?  ";
  cin >>size;

  long enteredNumbers[10000];
  long frequencyArray[10000];

  enternumber(enteredNumbers,size);

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
