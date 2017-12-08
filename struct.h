#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <vector>
#include <string>

using std::string;
template <class T>
class Iterator;

class Struct : public Term
{
  public:
    Struct(Atom const &name, std::vector<Term *> args): _name(name), _args(args) {}

    Atom &name() {
      return _name;
    }

    string symbol() const
    {
        string ret = _name.symbol() + "(";
        for (int i = 0; i < (int)_args.size(); i++)
        {
            if (i == (int)_args.size() - 1)
            {
                ret += _args[i]->symbol();
            }
            else
            {
                ret += _args[i]->symbol() + ", ";
            }
        }
        ret += ")";
        return ret;
    }

    string value() const
    {
        string ret = _name.symbol() + "(";
        for (int i = 0; i < (int)_args.size(); i++)
        {

            if (i == (int)_args.size() - 1)
            {
                ret += _args[i]->value();
            }
            else
            {
                ret += _args[i]->value() + ", ";
            }
        }
        return ret + ")";
    }

    bool match(Term &term)
    {
        Struct *ps = dynamic_cast<Struct *>(&term);
        if (ps)
        {
            if (!_name.match(ps->_name))
                return false;
            if (_args.size() != ps->_args.size())
                return false;
            for (int i = 0; i < _args.size(); i++)
            {
                if (_args[i]->symbol() != ps->_args[i]->symbol())
                    return false;
            }
            return true;
        }
        return false;
    }

    int arity() {
      return _args.size();
    }

    Term *args(int index) {
      return _args[index];
    }

    bool match(Variable &var) {
      return var.match(*this);
    }

    Struct *getStruct() {
      return this;
    }
    
    Iterator<Term *> *createIterator();
    Iterator<Term *> *createDFSIterator();
    Iterator<Term *> *createBFSIterator();

  private:
    Atom _name;
    std::vector<Term *> _args;
};

#endif
