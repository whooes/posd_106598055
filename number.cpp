#include "number.h"



Number::Number(double n) {
  std::stringstream ss;
    ss << n;
    ss >> _symbol;

}


  string Number::symbol() const {
    return _symbol;
}


  bool Number::match(Term &term){
      return value() == term.value();
    }


/*  bool Number::match(Variable &var){
    return var.match(*this);
  }*/
