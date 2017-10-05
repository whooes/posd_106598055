#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
using std::string;


class Atom :public Term{

  public:

    Atom(string s):Term(s){}
    bool variable(){
      return false;
    }
    bool match(Term &t){
      if(t.variable()){
        return t.match(*this);
      }
      return symbol() == t.symbol();
    }
  private:
};


#endif
