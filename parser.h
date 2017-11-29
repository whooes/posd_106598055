#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "number.h"
#include "utParser.h"
#include "node.h"
#include <typeinfo>

using std::string;
using namespace std;

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
      else
        return atom;
    }
    else if(token == '['){
      return list();
    }
    return nullptr;
  }


  Term * structure() {
    _inStruct = true;
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    _isStruct = true;
    createTerms();
    if(_currentToken == ')')
    {
      _inStruct = false;
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _nodeTerms.erase(_nodeTerms.begin() + startIndexOfStructArgs, _nodeTerms.end());
      checkVar(args);
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      _nodeTerms.erase(_nodeTerms.begin() + startIndexOfListArgs, _nodeTerms.end());
      checkVar(args);
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

  void matchings() {
    createTerms();
    int commaCount = 0;
    int commaPosition;
    int semicolonCount = 0;
    int semicolonPosition;
    for (int i = 0; i < _nodeTreeOperator.size(); i++){
      if (_nodeTreeOperator[i] -> payload == EQUALITY){
        _nodeTreeOperator[i] -> left = _nodeTerms[i];
        _nodeTreeOperator[i] -> right = _nodeTerms[i + 1];
      }
      else if (_nodeTreeOperator[i] -> payload == COMMA){
        commaCount++;
        if (commaCount == 1){
          if (semicolonCount == 0){
            _root = _nodeTreeOperator[i];
          }
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          commaPosition = i;
        }
        else if (commaCount >= 2){
          _nodeTreeOperator[commaPosition] -> right = _nodeTreeOperator[i];
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          commaPosition = i;
        }
      }
      else if (_nodeTreeOperator[i] -> payload == SEMICOLON){
        semicolonCount++;
        if (semicolonCount == 1){
          _root = _nodeTreeOperator[i];
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          semicolonPosition = i;
        }
        else if (semicolonCount >= 2){
          _nodeTreeOperator[semicolonPosition] -> right = _nodeTreeOperator[i];
          _nodeTreeOperator[i] -> left = _nodeTreeOperator[i - 1];
          semicolonPosition = i;
        }
      }
    }
    if(commaCount > 0){
    _nodeTreeOperator[commaPosition] -> right = _nodeTreeOperator[commaPosition + 1];
    }
    if(semicolonCount > 0){
      if(commaCount == 0){
        _nodeTreeOperator[semicolonCount] -> right = _nodeTreeOperator[semicolonPosition + 1];
      }
      else{
        _nodeTreeOperator[semicolonPosition] -> right = _nodeTreeOperator[semicolonCount + 2];
      }
    }
  }
  Node * expressionTree(){
    if (_nodeTreeOperator.size() == 1){
      return _nodeTreeOperator[0];
    }
    return _root;
  }

  Operators getEnums(int op){
    switch (op){
      case ';':
        return SEMICOLON;
        break;
      case ',':
        return COMMA;
        break;
      case '=':
        return EQUALITY;
        break;
      default:
        return TERM;
    }
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _nodeTerms.push_back(new Node(getEnums(_currentToken), term, nullptr, nullptr));
      _terms.push_back(term);
      if (_isStruct){
        _structPosition.push_back(_terms.size() - 1);
        _isStruct = false;
      } 
      if (isExist(term, _terms)){
        _nodeTerms[_nodeTerms.size() - 1] = _nodeTerms[_symbolPosition];
        _terms[_terms.size() - 1] = _terms[_symbolPosition];
      }
      while((_currentToken = _scanner.nextToken()) == ',' || _currentToken == '=' || _currentToken == ';') {
        _treeOperator.push_back(_currentToken);
        _nodeTreeOperator.push_back(new Node(getEnums(_currentToken)));
        Term * _termInWhile = createTerm();
        _nodeTerms.push_back(new Node(getEnums(_currentToken), _termInWhile, nullptr, nullptr));
        _terms.push_back(_termInWhile);
        if (_nodeTreeOperator[_nodeTreeOperator.size() - 1] -> payload != SEMICOLON){
          if (isExist(_termInWhile, _terms)){
            _nodeTerms[_nodeTerms.size() - 1] = _nodeTerms[_symbolPosition];
            _terms[_terms.size() - 1] = _terms[_symbolPosition];
          }
        }
      }
    }
  }

  bool isExist(Term * term, vector<Term*> terms){
    for (int i = terms.size() - 2; i >= 0; i--){
      if (_currentToken == VAR && (terms[i] -> symbol() == term -> symbol())){
          _symbolPosition = i;
          return true;
      }
      else if (_currentToken == VAR && _structPosition.size() != 0 && !_inStruct){
        for (int j = 0; j < _structPosition.size(); j++){
          for (int k = 0; k < dynamic_cast<Struct *>(terms[_structPosition[j]]) -> _args.size(); k++){
            if (term -> symbol() == dynamic_cast<Struct *>(terms[_structPosition[j]]) -> _args[k] -> symbol()){
              dynamic_cast<Struct *>(terms[_structPosition[j]]) -> _args[k] = term;
            }
          }
        }
      }
    }
    return false;
  }

  void checkVar(vector<Term *> args){
    for (int i = 0; i < _terms.size(); i++){
      for (int j = 0; j < args.size(); j++){
        if ((args[j] -> symbol()) == (_terms[i] -> symbol())){
          args[j] = _terms[i];
        }
      }
    }
  }

    vector<Node *> _nodeTerms;
    vector<Node *> _nodeTreeOperator;
    int _symbolPosition;
    bool _isStruct = false;
    bool _inStruct = false;
    vector<int> _structPosition;
    vector<int> _treeOperator;
    vector<Term *> _terms;
    Scanner _scanner;
    int _currentToken;
    Node * _root = nullptr;
};
#endif
