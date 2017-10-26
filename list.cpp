#include "list.h"


List::List(): _elements() {}

List::List(vector<Term *> const & elements):_elements(elements){}

Term * List::head() const{
  if(_elements.empty())
  {
    throw string("Accessing head in an empty list");
  }
  return _elements[0];
}

List * List::tail() const{
  if(_elements.empty())
  {
    throw string("Accessing tail in an empty list");
  }
  std::vector<Term *> v;
  for(unsigned int i = 1 ; i < _elements.size(); i++)
  {
    v.push_back(_elements[i]);
  }
  List *X = new List(v);
  return X;
}

string List::symbol() const{
  string s = "";
  if(_elements.empty())
    return "[]";
  for(unsigned int i = 0 ; i < _elements.size() - 1 ; i++)
  {
    s += (_elements[i] -> symbol() + ", ");
  }
  return "[" + s + _elements[_elements.size() - 1 ]-> symbol() + "]" ;
}

string List::value() const{
  string s = "";
  if(_elements.empty())
    return "[]";
    for(unsigned int i = 0 ; i < _elements.size() - 1 ; i++)
    {
      s += (_elements[i] -> value() + ", ");
    }
    return "[" + s + _elements[_elements.size() - 1 ]-> value() + "]" ;
}

bool List::match(Term &term){
  List *X = dynamic_cast<List *>(&term);
  if(X){

    if(_elements.size() != X ->_elements.size())
      return false;
      for(unsigned int i = 0 ;i < _elements.size(); i++)
      {
        if(!(_elements[i]-> match(*(X->_elements[i]))))
        return false;
      }

      return value() == term.value();
  }
  return true;

}
