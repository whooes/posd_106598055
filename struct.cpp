#include "struct.h"

Struct::Struct(Atom const & name , std::vector<Term *> args):_name(name), _args(args){}

Term * Struct::args(int index){
    return _args[index];
    }

Atom const & Struct::name(){
      return _name;
    }

string Struct::symbol() const{
      string ret = _name.symbol()+"(";
        for(int i = 0; i < (int)_args.size(); i++){
          if(i == (int)_args.size() - 1)
          {
            ret += _args[i] -> symbol();
          }
          else
          {
            ret += _args[i] -> symbol() + ", ";
          }
        }
      ret +=")";
      return ret;
    }

bool Struct::match(Term &term){
      Struct * ps = dynamic_cast<Struct *>(&term);
      if(ps){
          if (!_name.match(ps->_name))
            return false;
          if(_args.size()!= ps->_args.size())
            return false;
          for(int i = 0 ; i < _args.size() ;i++){
            if(_args[i]->symbol() != ps->_args[i]->symbol())
              return false;
          }
          return true;
      }

      return false;
    }
    
string Struct::value() const {

  string str = _name.symbol() + "(" ;

  for (int i=0 ; i < _args.size()- 1 ; i++){
    str += _args[i] -> value() + ", ";
  }
  str += _args[_args.size()-1] -> value() + ")" ;
  return str;
}

bool Struct::match(Variable &var) { return var.match(*this); }

int Struct::arity(){
  return _args.size();
}
Struct *Struct::getStruct(){
  return this;
}
