#include "struct.h"
#include "variable.h"
#include "atom.h"
#include "list.h"
#include "parser.h"
#include "scanner.h"
#include "number.h"
#include "iterator.h"

#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv){
  string input;
  string tempInput;
  while(true){
    input = "";
    cout << "?-";
    while(true){
      getline(cin, tempInput);
      if(tempInput == "halt." && input == "")
        return 0;
      input += tempInput;
      if(input == ""){
        break;
      }
      if(input[input.length()-1] == '.'){
        Scanner s(input);
        Parser p(s);
        try{
          p.buildExpression();
          Node *expressionTree = p.expressionTree();
          expressionTree->evaluate();
          string result = expressionTree->getResult();
          cout << result << endl;
          break;
        }catch(std::string &msg){
            cout << msg << endl;
            break;
         }
       }
       cout << "|  ";
     }
   }
 }
