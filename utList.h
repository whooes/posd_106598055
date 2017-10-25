#ifndef UTLIST_H
#define UTLIST_H

#include <string>
using std::string;

#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  List X ;
  EXPECT_EQ("[]", X.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[496, 8128]"
TEST(List, Numbers) {
  Number num1(8128);
  Number num2(496);
  std::vector<Term *> v = {&num2, &num1};
  List X(v);
  EXPECT_EQ("[496, 8128]", X.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  std::vector<Term *> v = {&terence_tao, &alan_mathison_turing};
  List X(v);
  EXPECT_EQ("[terence_tao, alan_mathison_turing]", X.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
  Variable X("X");
  Variable Y("Y");
  std::vector<Term *> v ={&X, &Y};
  List l(v);
  EXPECT_EQ("[X, Y]", l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
  Atom tom("tom");
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v = {&num, &X, &terence_tao};
  List l(v);
  EXPECT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number num1(8128);
  Number num2(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v = {&num2, &X, &terence_tao};
  List l(v);
  EXPECT_FALSE(num1.match(l));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term *> v = {&num, &X, &terence_tao};
  List l(v);
  std::vector<Term *> v1 = {&X};
  Struct s(Atom("s"), v1);
  EXPECT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term*> v ={ &num, &num, &X};
  List l(v);
  EXPECT_TRUE(Y.match(l));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Variable X("X");
  Number num(496);
  Atom terence_tao("terence_tao");
  std::vector<Term*> v = { &num, &X, &terence_tao};
  List l(v);
  EXPECT_FALSE(!X.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number num(496);
  Variable X("X");
  Atom terence_tao("terence_tao");
  std::vector<Term*> v = { &num, &X, &terence_tao};
  List l(v);
  List M(v);
  EXPECT_TRUE(l.match(M));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number num(496);
  Variable X("X");
  Variable Y("Y");
  Atom terence_tao("terence_tao");
  std::vector<Term*> v2 ={&num, &X, &terence_tao};
  std::vector<Term*> v1 ={&num, &Y, &terence_tao};
  List l(v2);
  List M(v1);
  EXPECT_TRUE(l.match(M));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number num1(496);
  Variable X("X");
  Number num2(8128);
  Atom terence_tao("terence_tao");
  std::vector<Term*> v1 ={&num1, &X, &terence_tao};
  std::vector<Term*> v2 ={&num1, &num2, &terence_tao};
  List l(v1);
  List M(v2);
  l.match(M);
  EXPECT_TRUE(X.match(num2));
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable Y("Y");
  Variable X("X");
  Number num(496);
  Atom terence_tao("terence_tao");
  Atom alan_mathison_turing("alan_mathison_turing");
  X.match(alan_mathison_turing);
  std::vector<Term*> v ={&num , &X, &terence_tao};
  List l(v);
  Y.match(l);
  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());
  EXPECT_TRUE(X.match(alan_mathison_turing));
}

// Example:
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("first"), l.head()->symbol());
  EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);

  EXPECT_EQ(string("second"), l.tail()->head()->value());
  EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args1 = {&f};
  List l(args1);
  vector<Term *> args2 = {&l, &s, &t};
  List M(args2);
  EXPECT_EQ(string("[first]"), M.head()->value());
  EXPECT_EQ(string("[second, third]"), M.tail()->value());

}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
  Atom f("first"), s("second"), t("third");
  vector<Term *> args = {&f, &s, &t};
  List l(args);
  EXPECT_EQ(string("third"), l.tail()->tail()->head()->value());
  EXPECT_EQ(string("[]"), l.tail()->tail()->tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST (List, emptyExecptionOfHead) {
  List l;
  string s;
  try{
    s = l.head()->value();
  }catch(const string x){
    EXPECT_EQ("Accessing head in an empty list", x);
  }
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST (List, emptyExecptionOfTail) {
  List l;
  string s;
  try{
    s = l.tail()->value();
  }catch(const string x){
    EXPECT_EQ("Accessing tail in an empty list", x);
  }
}




#endif
