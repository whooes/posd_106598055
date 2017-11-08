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
    if (term.getVar()) {
      return term.match(*this);
    } else {
      return value() == term.value();
    }
  }
