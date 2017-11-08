#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>
using std::vector;

class List : public Term
{
public:

  List();

  List(vector<Term *> const &elements);

  Term *head() const;

  List *tail() const;

  string symbol() const;

  string value() const;

  bool match(Term &term);

  List *getList();


private:
  vector<Term *> _elements;
};

#endif
