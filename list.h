#ifndef LIST_H
#define LIST_H
#include <typeinfo>
#include "term.h"
#include "variable.h"
#include <vector>
#include <string>
using std::vector;

class List : public Term {
public:
  List():_elements(){}
  List (vector<Term *> const & elements):_elements(elements){}

  string symbol() const{
    string ret = "[";
    if (_elements.size() == 0){
      ret += "]";
      return ret;
    }
    else {
      for(int i = 0; i < _elements.size() - 1 ; i++){
        ret += _elements[i] -> symbol() + ", ";
      }
      ret += _elements[_elements.size()-1] -> symbol() + "]";
    }
    return ret;
  }
  std::string value() const{
    std::string ret = "[";
    if (_elements.size() == 0){
      ret += "]";
      return ret;
    }
    else {
      for(int i = 0; i < _elements.size() - 1; i++){
          ret += _elements[i] -> value() + ", ";
      }
        ret += _elements[_elements.size()-1] -> value() + "]";
      return ret;
    }
  }
  bool match(Term & term){
      List * pl = dynamic_cast<List *>(&term);
      Variable * pv = dynamic_cast<Variable *>(&term);
      if (pl){
        std::vector<Term *> pl_temp = pl -> getElements();
        if (_elements.size() != pl_temp.size())
          return false;
        for (int i = 0; i < _elements.size(); i++){
          if (!(_elements[i] -> match(*pl_temp[i]))){
              return false;
          }
        }
        return true;
      }
      else if (pv){
        return pv -> match(*this);
      }
      else{
        return symbol() == term.symbol();
      }
  }

  Term * head() const{
      Term * ret = NULL;
      if (_elements.size() <= 0)
        throw std::string("Accessing head in an empty list");
      else{
        ret = _elements[0];
        return ret;
      }
  }

  List * tail() const{

      std::vector<Term *> temp = {};
      temp = _elements;
      if (temp.size() == 0)
        throw std::string("Accessing tail in an empty list");
      else{
        temp.erase(temp.begin());
        return new List(temp);
      }
  }

  vector<Term *> getElements(){
    return _elements;
  }

private:
  vector<Term *> _elements;
};

#endif
