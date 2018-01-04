#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <vector>

using std::vector;
template <class T>
class Iterator;

class List : public Term
{
  public:
    string symbol() const
    {
        string ret = "[";
        for (int i = 0; i < (int)_elements.size(); i++)
        {
            if (i == (int)_elements.size() - 1)
            {
                ret += _elements[i]->symbol();
            }
            else
            {
                ret += _elements[i]->symbol() + ", ";
            }
        }
        return ret + "]";
    }

    string value() const
    {
        string ret = "[";
        for (int i = 0; i < (int)_elements.size(); i++)
        {
            if (i == (int)_elements.size() - 1)
            {
                ret += _elements[i]->value();
            }
            else
            {
                ret += _elements[i]->value() + ", ";
            }
        }
        return ret + "]";
    }

    bool match(Term &term)
    {
        if (term.getVariable())
        {
            return term.match(*this);
        }
        else if (List *pl = term.getList())
        {
            if (_elements.size() != pl->_elements.size())
            {
                return false;
            }
            else
            {
                for (int i = 0; i < _elements.size(); i++)
                {
                    if (!_elements[i]->match(*(pl->_elements[i])))
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
    int arity() { return _elements.size(); }
    Term *args(int index) { return _elements[index]; }
    List *getList() { return this; }
    Iterator<Term *> *createIterator();
    Iterator<Term *> *createDFSIterator();
    Iterator<Term *> *createBFSIterator();

  public:
    List() : _elements() {}
    List(vector<Term *> const &elements) : _elements(elements) {}
    Term *head() const
    {
        if (_elements.empty())
        {
            throw string("Accessing head in an empty list");
        }
        else
        {
            return _elements[0];
        }
    }

    List *tail() const
    {
        if (_elements.empty())
        {
            throw string("Accessing tail in an empty list");
        }
        else
        {
            List *tempList = new List(vector<Term *>(
                _elements.end() - _elements.size() + 1, _elements.end()));
            return tempList;
        }
    }

    vector<Term *> elements() const { return _elements; }

  private:
    vector<Term *> _elements;
};

#endif
