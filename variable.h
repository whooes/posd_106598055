#ifndef VARIABLE_H
#define VARIABLE_H

#include "term.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

class Variable : public Term {
public:
  Variable(string s);

  string symbol() const;

  string value() const;

  bool match(Term &term);

  Variable *getVariable();

private:
  string _symbol;
  bool _assignable = true;
  Term *_value = NULL;
  int _vectorPointer = -1;
};

#endif
