#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include <string>
using std :: string;
#include <iostream>
using namespace std;

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getResultTree() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  bool evaluate(){
    return _left->match(*_right);
  }

  string getResultTree(){
    string temp;
    // cout << _left -> value() << endl;
    // cout << _right -> value();
    temp += _left -> value();
    temp += " = " ;
    temp += _right -> value();
    return temp;
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

  string getResultTree(){
    return "456";
  }

private:
  Exp * _left;
  Exp * _right;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

    string getResultTree(){
      return "789";
    }

private:
  Exp * _left;
  Exp * _right;
};
#endif
