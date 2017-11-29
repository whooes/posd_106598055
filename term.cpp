#include "term.h"
#include "variable.h"
#include <iostream>
#include <typeinfo>

bool Term::match(Term & term){
  if (typeid(term) == typeid(Variable))
    return term.match(*this);
  else{
    return symbol() == term.symbol();
  }
}
