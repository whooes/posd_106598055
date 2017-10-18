#include "number.h"



Number::Number(double n) {
  string str = std::to_string(n);
  for(int i = str.size() - 1 ; i >= 0 ; i-- ){
    if(str[i] == '0' || str[i] == '.')
    str.pop_back();
    else
      break;
  }
  _symbol = str;
}


  string Number::symbol() const {
    return _symbol;
}


  bool Number::match(Term &term){
      return value() == term.value();
    }


  bool Number::match(Variable &var){
    return var.match(*this);
  }
