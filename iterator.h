#ifndef ITERATOR_H
#define ITERATOR_H

#include "struct.h"
#include "list.h"
#include "atom.h"
#include "node.h"
#include <stack>
#include <queue>
#include <iostream>

using std::queue;
using std::stack;

template<class T>
class Iterator{
public:
    virtual Term * currentItem() const = 0;
    virtual bool isDone() const = 0;
    virtual void first() = 0;
    virtual void next() = 0;
};

template<class T>
class NullIterator : public Iterator<T>{
public:
  NullIterator(Term *n){}
  Term * currentItem() const {
    return nullptr;
  }
  bool isDone() const{
    return true;
  }
  void first(){}
  void next(){}
};

template<class T>
class StructIterator :public Iterator<T> {
public:
  StructIterator(Struct *s): _index(0), _struct(s) {}

  void first() {
    _index = 0;
  }

  Term* currentItem() const {
    return _struct->args(_index);
  }

  bool isDone() const {
    return _index >= _struct->arity();
  }

  void next() {
    _index++;
  }
private:

  int _index;
  Struct* _struct;
};



template<class T>
class ListIterator : public Iterator<T>{
public:

  ListIterator(List *list): _index(0), _list(list){}

  Term * currentItem() const{
    return _list -> args(_index);
  }
  bool isDone() const{
    return _index >= _list ->arity();
  }
  void first(){
    _index = 0;
  }

  void next(){
    _index++;
  }

private:

  int _index;
  List *_list;
};

template<class T>
class DFSIterator : public Iterator<T>{
public:
  DFSIterator(T t) : _t(t) {}

  Term *currentItem() const
  {
    return _nowIterator;
  }

  bool isDone() const
  {
    return _stack.empty();
  }

  void first()
  {
    _nowIterator = _t;
    while (!_stack.empty())
    {
        _stack.pop();
    }

    for (int i = (int)_nowIterator->arity() - 1; i >= 0; i--)
    {
        _stack.push(_nowIterator->args(i));
    }

    if (!_stack.empty())
    {
        next();
    }
  }

  void next()
  {
    if (!isDone())
    {
        _nowIterator = _stack.top();
        _stack.pop();
        for (int i = (int)_nowIterator->arity() - 1; i >= 0; i--)
        {
            _stack.push(_nowIterator->args(i));
        }
    }
  }

private:
  T _t;
  stack<T> _stack;
  T _nowIterator;
};

template<class T>
class BFSIterator : public Iterator<T>{
public:
  BFSIterator(T t) : _t(t) {}

  Term *currentItem() const
  {
      return _nowIterator;
  }

  bool isDone() const
  {
      return _queue.empty();
  }

  void first()
  {
      _nowIterator = _t;
      while (!_queue.empty())
      {
          _queue.pop();
      }

      for (int i = 0; i < (int)_nowIterator->arity(); i++)
      {
          _queue.push(_nowIterator->args(i));
      }

      if (!_queue.empty())
      {
          next();
      }
  }

  void next()
  {
      if (!isDone())
      {
          _nowIterator = _queue.front();
          _queue.pop();
          for (int i = 0; i < (int)_nowIterator->arity(); i++)
          {
              _queue.push(_nowIterator->args(i));
          }
      }
  }

  private:
    T _t;
    queue<T> _queue;
    T _nowIterator;
};
#endif
