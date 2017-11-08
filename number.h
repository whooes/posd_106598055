#ifndef NUMBER_H
#define NUMBER_H

#include <sstream>
#include "term.h"
#include "variable.h"
#include <string>
using std::string;

class Number : public Term {
public:
  Number(double n);

  string symbol() const;

  bool match(Term &term);

private:
  string _symbol;
};

#endif
