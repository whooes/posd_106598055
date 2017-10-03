#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"

using std::string;
using std::to_string;

class Variable : public Term{

  public:
    Variable(string s):Term(s),_assignValue(s){}

    string symbol(){
    return  _assignValue;
    }
    string value(){
      return _assignValue;
    }
    bool variable(){
      return true;
    }
    bool match(Term &t){
      if(_assignable){
        _assignValue = t.symbol();
        _assignable = false;
        return true;
      }else{
        if(_assignValue == t.symbol())
          return true;
        else
          return false;
        }
    }

  private:
    bool _assignable = true;
    string _assignValue;
};
#endif
