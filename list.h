#ifndef LIST_H
#define LIST_H

#include "term.h"

#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const;
  string value() const;
  bool match(Term &term);

  List ();
  List (vector<Term *> const & elements);
  Term * head() const;
  List * tail() const;

  List *getList(){return this;}

private:
  vector<Term *> _elements;

};

#endif
