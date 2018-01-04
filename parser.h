#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;
#include <stack>
using std::stack;

#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "number.h"
#include "node.h"


class Parser
{
  public:
    Parser(Scanner scanner) : _scanner(scanner), _terms() {}

    Term *createTerm(){
        int token = _scanner.nextToken();
        _currentToken = token;
        if(token == VAR){
          return new Variable(symtable[_scanner.tokenValue()].first);
        }
        else if(token == NUMBER){
          return new Number(_scanner.tokenValue());
        }
        else if (token == ATOM || token == ATOMSC)
        {
            Atom *atom = new Atom(symtable[_scanner.tokenValue()].first);
            if(_scanner.currentChar() == '('){
                return structure();
            }
            else
              return atom;
        }
        else if (token == '['){
          return list();
        }
        return nullptr;
    }

    Term *structure()
    {
        Atom structName = Atom(symtable[_scanner.tokenValue()].first);
        int startIndexOfStructArgs = _terms.size();
        _scanner.nextToken();
        createTerms();
        if(_currentToken == ')'){
            vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
            _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
            return new Struct(structName, args);
        }
        else{
          throw string("Unbalanced operator");
        }
    }

    Term *list()
    {
        int startIndexOfListArgs = _terms.size();
        createTerms();
        if (_currentToken == ']'){
          vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
          _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
          return new List(args);
        }
        else{
          throw string("Unbalanced operator");
        }
    }

    vector<Term *> &getTerms() { return _terms; }

    void matchings(){ _tree = buildExpressionTree(NULL); }

    void buildExpression()
    {
        _tree = buildExpressionTree(NULL);
        if(_tree->payload == TERM)
          throw string(_tree->term->symbol() +" does never get assignment");

        stack<Node *> NodeStack;
        NodeStack.push(_tree);
        while(!NodeStack.empty()){
            Node *tempRoot = NodeStack.top();
            NodeStack.pop();
            if(tempRoot->payload != TERM){
                if(!tempRoot->right || !tempRoot->left){
                    throw string("Unexpected '" + tempRoot->operatorToString(tempRoot->payload) + "' before '.'");
                }
                if(tempRoot->payload == EQUALITY){
                    if(tempRoot->left->payload != TERM)
                       throw string(tempRoot->left->term->symbol() + " does never get assignment");
                    if(tempRoot->right->payload != TERM)
                       throw string(tempRoot->right->term->symbol() + " does never get assignment");
                }
            }
        }
    }

    Node *buildExpressionTree(Node *root)
    {
        if (_scanner.currentChar() == '.')
            return root;
        if (_scanner.skipLeadingWhiteSpace() >=_scanner.buffer.length())
            throw string("Missing token '.'");
        Term *term = NULL;
        Node *tempTree = NULL;
        char currentChar = _scanner.currentChar();
        if (!(currentChar == ';' || currentChar == ',' || currentChar == '=')){
          term = createTerm();
          _scanner.skipLeadingWhiteSpace();
          currentChar = _scanner.currentChar();
        }
        if(currentChar == ';' || currentChar == ',' || currentChar == '=')
        {
          _scanner.extractChar();
        }

        if(currentChar == ';'){
          _subTreeTerms.clear();
          tempTree = new Node(SEMICOLON, nullptr, nullptr, nullptr);
          if(root && SEMICOLON >= root->payload){
            addNodeToSubTree(root, tempTree);
            return buildExpressionTree(root);
          }
          else{
            tempTree->left = root;
            return buildExpressionTree(tempTree);
          }
        }
        else if(currentChar == ',')
        {
          tempTree = new Node(COMMA, nullptr, nullptr, nullptr);
          if (root && COMMA >= root->payload){
            addNodeToSubTree(root, tempTree);
            return buildExpressionTree(root);
          }
          else{
            tempTree->left = root;
            return buildExpressionTree(tempTree);
          }
        }
        else if(currentChar == '=')
        {
          term = checkTree(term);
          Node *tempNode = new Node(TERM, checkTree(term), nullptr, nullptr);
          _terms.push_back(term);
          tempTree = new Node(EQUALITY, nullptr, tempNode, nullptr);
          term = checkTree(createTerm());
          tempTree->right = new Node(TERM, term, nullptr, nullptr);
          _terms.push_back(term);
          if(root){
            addNodeToSubTree(root, tempTree);
            return buildExpressionTree(root);
          }
          else{
            return buildExpressionTree(tempTree);
          }
        }
        else
        {
          term = checkTree(term);
          Node *tempTree = new Node(TERM, checkTree(term), nullptr, nullptr);
          _terms.push_back(term);
          if(root){
            addNodeToSubTree(root, tempTree);
            return buildExpressionTree(root);
          }
          else{
              return buildExpressionTree(tempTree);
          }
        }
        return NULL;
    }

    void addNodeToSubTree(Node *root, Node *subTree)
    {
      Node *tempNode = root;
      while (tempNode->right)
      {
        if(subTree->payload < tempNode->right->payload){
          subTree->left = tempNode->right;
          tempNode->right = subTree;
          return;
        }
        tempNode = tempNode->right;
      }
      if(!tempNode->left){
        tempNode->left = subTree;
      }
      else{
        tempNode->right = subTree;
      }
    }

    Term *checkTree(Term *term)
    {
        createSubTreeTable(term);
        Variable *v = dynamic_cast<Variable *>(term);
        if(v){
            for(int i=0; i<(int)_subTreeTerms.size(); i++){
                if(_subTreeTerms[i]->symbol() == term->symbol()){
                  return _subTreeTerms[i];
                }
            }
            _subTreeTerms.push_back(term);
        }
        return term;
    }

    void createSubTreeTable(Term *t)
    {
        Struct *s = dynamic_cast<Struct *>(t);
        if(s)
        {
          for(int i=0; i<(int)s->arity(); i++){
            createSubTreeTable(s->args(i));
          }
        }
        List *l = dynamic_cast<List *>(t);
        if(l){
          for(int i = 0; i < (int)l->arity(); i++){
            createSubTreeTable(l->args(i));
          }
        }
        Variable *v = dynamic_cast<Variable *>(t);
        if(v){
          for(int i=0; i<(int)_subTreeTerms.size(); i++){
            if(_subTreeTerms[i]->symbol() == t->symbol()){
              _subTreeTerms[i]->match(*t);
                return;
            }
          }
          _subTreeTerms.push_back(t);
        }
    }

    Node *expressionTree() {  return _tree;  }

  private:

    void createTerms(){
        Term *t = createTerm();
        if (t != nullptr){
            _terms.push_back(t);
            while ((_currentToken = _scanner.nextToken()) == ','){
              _terms.push_back(createTerm());
            }
        }
    }

    int _currentToken;
    Node *_tree;
    vector<Term *> _terms;
    vector<Term *> _subTreeTerms;
    Scanner _scanner;


};
#endif
