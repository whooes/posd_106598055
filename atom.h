#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
#include "variable.h"

using std::string;


class Atom : public Term{

  public:

    Atom(string s):_symbol(s) {}

    bool match(Term &term){
      return value() == term.value();
    }

    bool match(Variable &var){
      return var.match(*this);
    }

    string symbol() const{
      return _symbol;
    }

  private:
    string _symbol;
};


#endif
