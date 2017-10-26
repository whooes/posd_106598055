#ifndef STRUCT_H
#define STRUCT_H


#include<string>
#include <vector>
#include "term.h"
#include "atom.h"


using std::string;
using std::to_string;

class Struct : public Term{
  public:
    Struct(Atom const & name , std::vector<Term *> args);

    Term * args(int index);

    Atom const & name();

    string symbol() const;

    bool match(Term & term);

    string value() const ;

  private:
    Atom _name;
    std::vector<Term *> _args;
};
#endif
