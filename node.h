#ifndef NODE_H
#define NODE_H

enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

using namespace std;

class Node {
  public:
    Node(Operators op):payload(op), term(0), left(0), right(0) {}

    Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}

  bool evaluate(){
    while (left != 0 && right != 0){
      left -> evaluate();
      right -> evaluate();
      if (left -> payload == TERM){
        return (left -> term) -> match(*(right -> term));
      }
      else
        break;
    }
  }

  Operators payload;
  Term *term;
  Node *left;
  Node *right;
};

#endif
