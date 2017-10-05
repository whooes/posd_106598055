#ifndef NUMBER_H
#define NUMBER_H

#include<string>
#include "term.h"
#include <iostream>

using std::string;
using std::to_string;

class Number : public Term{

  public:

  Number(int s) : Term(to_string(s)),_number(s){}
    string value(){
      return symbol();
    }
    bool var(){
      return false;
    }


    bool match(Term &t){
      if(t.var()){
        return t.match(*this);
      }
      return symbol() == t.symbol();
  }

private:
    int _number;
};


#endif
