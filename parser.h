#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "number.h"
#include "list.h"

using std::string;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }
    else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }
    else if(token == ATOM || token == ATOMSC)
    {
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(') {
          _scanner.extractChar();
          vector<Term *> terms = getArgs();
          if (terms.empty() || _currentToken == ')')
              return new Struct(*atom, terms);
          else
              throw string("unexpected token");
      }
      else
          return atom;
    }
    else if (token == LIST)
    {
      _scanner.extractChar();
      vector<Term *> terms = getArgs();
      if (terms.empty() || _currentToken == ']')
          return new List(terms);
      else
          throw string("unexpected token");
    }
    return nullptr;
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(!term)
      return args;
    args.push_back(term);
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }



private:
  Scanner _scanner;
  int _currentToken;

};
#endif
