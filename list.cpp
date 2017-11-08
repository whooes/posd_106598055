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
  else
  {
    List *t = new List(vector<Term *>(
        _elements.end() - _elements.size() + 1, _elements.end()));
    return t;
  }
}

string List::symbol() const{
  string s = "[";

  for(int i = 0; i<(int)_elements.size(); i++)
  {
    if(i == (int)_elements.size() -1)
    {
      s += _elements[i]->symbol();
    }
    else
    {
      s += _elements[i]->symbol() + ", ";
    }
  }
  return s + "]";
}

string List::value() const{
  string s = "[";

    for(int i = 0; i<(int)_elements.size(); i++)
    {
      if(i == (int)_elements.size() -1)
      {
        s += _elements[i]->symbol();
      }
      else
      {
        s += _elements[i]->symbol() + ", ";
      }
    }
    return s + "]";
  }

bool List::match(Term &term){
  if (term.getVar())
    {
      return term.match(*this);
    }
    else if (List *X = term.getList())
    {
      if (_elements.size() != X->_elements.size())
      {
        return false;
      }
      else
      {
        for (int i = 0; i < _elements.size(); i++)
        {
          if (!_elements[i]->match(*(X->_elements[i])))
            return false;
        }
        return true;
      }
    }
    else
    {
      return false;
    }
  }

  List *List::getList(){return this;}
