include <iostream>
#include <string>
#include "expr_eval.h"
#include <math.h>
#include <sstream>
#include <cctype>
#include <ctype.h>
#include "mystack.h"
#include <stdlib.h>
//#include <stack>                                                                                                                                                                                                                                                                                                                                                          
#include <iomanip>
using namespace std;
mystack <double> operands;
mystack <string> operators;
//stack <double> operands;                                                                                                                                                                                                                                                                                                                                                  
//stack <string> operators;                                                                                                                                                                                                                                                                                                                                                 
bool error;
std::string num,oper,trig;
double number = -1;
int len;
char i;
int err = 0;
//true if op1 priority > op2, false if op1 priority < op2                                                                                                                                                                                                                                                                                                                   
bool hasLowerPriority(char op1, char op2){
  switch (op1){
  case '(': return false;
  case '-': return op2 == '-' || op2 == '+';
  case '+': return op2 == '-' || op2 == '+';
  case '*': return op2 != '/';
  case '/': return true;
  case '^': return op2 != '(';
  case 's': return op2 != '(';
  case 'c': return op2 != '(';
  case 't': return op2 != '(';
  case 'l': return op2 != '(';
  default : err = 1;error = true; return false;
  }
}
// perform the operation 'op' on the two(or one) operands on top of the stack                                                                                                                                                                                                                                                                                               
void operation(char op) {
  double op1 = -1;
  //Do single num operations first                                                                                                                                                                                                                                                                                                                                          
  if(op == 's'){
    if(operands.size() >=1){
    op1 = operands.top();operands.pop();
    operands.push(sin(M_PI * op1 / 180.0));
    return;
    }else{
      err = -1;error = true;return;
    }
  }else if(op == 'c'){
    if(operands.size() >=1){
      op1 = operands.top();operands.pop();
      operands.push(cos(M_PI * op1 / 180.0));
      return;
    }else{
      err = -1;error = true;return;
    }
  }else if(op == 't'){
    if(operands.size() >=1){
      op1 = operands.top();operands.pop();
      operands.push(tan(M_PI * op1 / 180.0));
      return;
    }else{
      err = -1;error = true;return;
    }
  }else if(op == 'l'){
    if(operands.size() >=1){
      op1 = operands.top();operands.pop();
      operands.push(log10(op1));
      return;
    }else{
      err = -1;error = true;return;
    }
  }
 //error handle if not single operand operator                                                                                                                                                                                                                                                                                                                             
  if(operands.size() < 2){
    err=3; error = true;return;
  }
  double op2 = operands.top();operands.pop();
  //first op is only poped if needed                                                                                                                                                                                                                                                                                                                                        
  if(op != 's'||op != 'c'||op != 't' || op != 'l'){
   op1 = operands.top();operands.pop();
  }
  switch(op){
  case '+': operands.push(op1 + op2);break;
  case '-': operands.push(op1 - op2);break;
  case '*': operands.push(op1 * op2);break;
  case '/': operands.push(op1 / op2);break;
  case '^': operands.push(pow(op1,op2));break;
  default : err = 2;error = true;return;
  }
}
string rep;
char repOper;
//given a epression return value if there is an x replace it with double x                                                                                                                                                                                                                                                                                                  
double eval(string exp,double x){
  double ret = 0;
  len = exp.length();
  if(len == 0){cout<<"error"<<endl;return ret;}
  exp += ')';
  err = 0;error = false;
  operators.push("(");
  for( int j = 0; j < exp.length();j++){
    if(!error){
      i = exp[j];
      rep = exp[j];
      if(isdigit(exp[j])||exp[j] == '.'){
        if(!isdigit(exp[j+1])&&exp[j+1]!='.'){
          num += exp[j];
          operands.push(atof(num.c_str()));
          num = "";
        }else{
          num+=exp[j];
        }
      }else if(exp[j] == 'x'){
        operands.push(x);
      }
      else switch(i){
        case '(': operators.push("(");break;
        case ')': while(!operators.empty() && !error && operators.top() != "("){
            oper = operators.top();
            repOper = oper[0];
            operation(repOper);operators.pop();
          }
          if(!operators.empty()){
            operators.pop();
          }else{
            err = 5; error = true;
          }
          break;
        default :
          oper = operators.top();
          repOper = oper[0];
  //disregard two other letters of sin cos tan log                                                                                                                                                                                                                                                                                                                  
          if(exp[j] == 'i'||exp[j] == 'n' || exp[j] == 'g'||exp[j]=='a'){
            break;
          }else if((exp[j] == 'o'&&exp[j+1]=='s')){
            j++;
            break;
          }else if(exp[j] == 'o'){
            break;
          }
          while(!operators.empty() && !error && hasLowerPriority(operators.top()[0],i)){
            //doing operation until the top op has lower priority                                                                                                                                                                                                                                                                                                           
            oper = operators.top();
            repOper = oper[0];
            operation(repOper);
            operators.pop();
          }
          //variable string rep to pass exp[j]                                                                                                                                                                                                                                                                                                                              
          operators.push(rep);
        }
    }
  }
  //check for errors and print answer                                                                                                                                                                                                                                                                                                                                       
  if(err != 0 || !operators.empty() || operands.size() !=1){
    cout<<"error"<<err<<endl;
    while(!operands.empty()){
      operands.pop();
    }
    while(!operators.empty()){
      operators.pop();
    }
  }else {
    ret = operands.top();
     operands.pop();
    return ret;
  }
  return ret;
}




int main(){
  //if line has an x in it next cin will be what x is equal to                                                                                                                                                                                                                                                                                                              
  std::string read;//string to read in expression                                                                                                                                                                                                                                                                                                                           
  std::string x = "x";//string to compare and find if x is in expression                                                                                                                                                                                                                                                                                                    
  double xVal = -1;//double variable to hold the x value if present                                                                                                                                                                                                                                                                                                         
  double ans;//double variable to hold returned answer from eval function                                                                                                                                                                                                                                                                                                   
  //reads until end of file                                                                                                                                                                                                                                                                                                                                                 
   while(cin >> read){
     //if x is found cin next line for value of x                                                                                                                                                                                                                                                                                                                           
    if(read.find(x) != std::string::npos){
      cin >> xVal;
    }
    ans = eval(read,xVal);
    cout << std::fixed << setprecision(2) << ans << endl;
    }
   // cout<<endl;                                                                                                                                                                                                                                                                                                                                                           
  return 0;
}
