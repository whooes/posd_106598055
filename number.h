#ifndef NUMBER_H
#define NUMBER_H

#include<string>
#include "term.h"
#include <iostream>
#include <sstream>
#include "variable.h"

using std::string;
using std::to_string;

class Number : public Term{

  public:

    Number(double n);

    string symbol() const;

    bool match(Term &term);

    bool match(Variable &var);

    private:
      string _symbol;
};


#endif
