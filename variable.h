#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
#include <vector>

using std::string;
using std::to_string;
using std::vector;

class Variable : public Term{

  public:
    Variable(string s);

    string symbol() const;

    string value() const;

    bool match(Term &term);


  private:
    bool _assignable = true;
    string _symbol;
    Term *_value = NULL;
};
#endif
