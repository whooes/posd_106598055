#include "variable.h"

Variable::Variable(string s):_symbol(s){}

string Variable::symbol() const{
  return _symbol;
}

string Variable::value() const{
  if(_value)
    return _value -> value();
  else
    return symbol();
}

bool Variable::match(Term &term){
  if(&term == this){
    return true;
  }
  if(!_value){
    _value = &term;
    return true;
  }
  else
    return _value ->match(term);
}

Variable *Variable::getVariable(){ return this; }
