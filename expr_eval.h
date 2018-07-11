#ifndef EXPR_EVAL_H
#define EXPR_EVAL_H

#include <string>
#include "mystack.h"

using namespace std;

class expr_eval{
  private:
  // Declare which ever necessary variables and methods                                                                                                                       
  bool hasLowerPriority(string,string);
  void operation(string op);
   public:
        double eval(string, double);
};




#endif
