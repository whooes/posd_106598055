#ifndef STRUCT_H
#define STRUCT_H

#include "atom.h"
#include "variable.h"
#include <vector>
#include <string>

using std::string;

class Struct: public Term {
public:
  Struct(Atom name, std::vector<Term *> args): _name(name) {
    _args = args;
  }

  int arity(){
    return _args.size();
  }

  Term * args(int index) {
    return _args[index];
  }

  Atom & name() {
    return _name;
  }

  string symbol() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    if (_args.size() == 0){
      ret += ")";
      return ret;
    }
    for (; it != _args.end()-1; ++it)
      ret += (*it)->symbol()+", ";
    ret  += (*it)->symbol()+")";
    return ret;
  }

  string value() const {
    string ret = _name.symbol() + "(";
    std::vector<Term *>::const_iterator it = _args.begin();
    for (; it != _args.end()-1; ++it)
      ret += (*it)->value()+", ";
    ret  += (*it)->value()+")";
    return ret;
  }
  
  bool match(Term &term){
    Struct * ps = dynamic_cast<Struct *>(&term);
    Variable * pv = dynamic_cast<Variable *>(&term);
    if (ps){
      std::vector<Term *> ps_temp = ps -> getArgs();
      if (!_name.match(ps -> _name))
        return false;
      if(_args.size() != ps -> _args.size())
        return false;
      for(int i = 0; i < _args.size(); i++){
        if (!(_args[i] -> match(*ps_temp[i])))
          return false;
      }
      return true;
    }
    else if (pv)
      return pv -> match(*this);
    else
      return symbol() == term.symbol();
  }
  std::vector<Term *> getArgs(){
    return _args;
  }
  std::vector<Term *> _args;
private:
  Atom _name;
};

#endif
