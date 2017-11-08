#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include <vector>
#include <string>

using std::string;

class Struct : public Term
{
public:
  Struct(Atom const &name, std::vector<Term *> args);

  int arity();

  Term *args(int index);

  Atom const &name();

  string symbol() const;

  string value() const;

  bool match(Term &term);

  bool match(Variable &var);

  Struct *getStruct();

private:
  Atom _name;
  std::vector<Term *> _args;
};

#endif
