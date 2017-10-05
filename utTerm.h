#ifndef UTTERM_H
#define UTTERM_H

//#include <gtest/gtest.h>
#include "term.h"
#include "number.h"
#include "atom.h"
#include "variable.h"
#include <iostream>
using namespace std;

//test Number.value()
TEST (Number,ctor) {
  Number number(7);
  ASSERT_EQ("7", number.value());
}
//test Number.symbol()
TEST (Number, symbol) {
  Number number(8);
 ASSERT_EQ("8",number.symbol());
}
//?- 25=25.
//true.
TEST (Number, matchSuccess) {
  Number number1(25);
  Number number2(25);
  EXPECT_TRUE(number1.match(number2));
}
//?- 25=0.
//false.
TEST (Number, matchFailureDiffValue) {
  Number number1(25);
  Number number2(0);
  EXPECT_FALSE(number1.match(number2));

}
//?- 25=tom.
//false.
TEST (Number, matchFailureDiffConstant) {
  Number number(25);
  Atom tom("tom");

  EXPECT_FALSE(number.match(tom));
}
//?- 25=X.
//true.
TEST (Number, matchSuccessToVar) {
  Number number(25);
  Variable X("X");
  EXPECT_TRUE(number.match(X));

}

//?- tom=25.
//false.
TEST (Atom, matchFailureDiffConstant) {
  Atom tom("tom");
  Number number(25);
  EXPECT_FALSE(tom.match(number));
}

// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom tom("tom");
  Variable X("X");
//cout << X.symbol() << endl;
  EXPECT_TRUE(tom.match(X));
  EXPECT_EQ("tom" ,X.symbol());
//cout << tom.symbol() << endl;
}

// ?- X=tom, tom=X.
// X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {

  Variable X("X");
  Atom tom("tom");
//  cout << tom.symbol() << endl;

  EXPECT_TRUE(X.match(tom));


  EXPECT_TRUE(tom.match(X));
  EXPECT_EQ("tom" ,X.symbol());

  //cout << tom.symbol() << endl;

}

// ?- X=jerry, tom=X.
// false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Variable X("X");
  Atom jerry("jerry");
  Atom tom("tom");
  EXPECT_TRUE(X.match(jerry));

  EXPECT_FALSE(tom.match(X));
  //cout << tom.symbol() << endl;

}

// ?- X = 5.
// X = 5.
TEST (Variable, matchSuccessToNumber) {
  Variable X("X");
  Number number(5);
  EXPECT_TRUE(X.match(number));
}

// ?- X=25, X= 100.
// false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
  Variable X("X");
  Number number1(25);
  Number number2(100);
  EXPECT_TRUE(X.match(number1));
  EXPECT_FALSE(X.match(number2));

}
// ?- X=tom, X= 25.
// false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
  Variable X("X");
  Atom tom("tom");
  Number number(25);
  EXPECT_TRUE(X.match(tom));
  EXPECT_FALSE(X.match(number));

}
//?- tom=X, 25=X.
//false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
  Atom tom("tom");
  Variable X("X");
  Number number(25);
  EXPECT_TRUE(tom.match(X));
  EXPECT_FALSE(number.match(X));
}
//?- X=tom, X=tom.
//true.
TEST(Variable, reAssignTheSameAtom){
  Variable X("X");
  Atom tom("tom");
  EXPECT_TRUE(tom.match(X));
  EXPECT_EQ("tom",X.symbol());
}
#endif
