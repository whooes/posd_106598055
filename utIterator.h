#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "atom.h"
#include "struct.h"
#include "list.h"
#include "iterator.h"
#include "number.h"
#include "variable.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    Iterator<Term *> * itStruct = s.createIterator();
    itStruct->first();
    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term *> * itStruct = s.createIterator();
  itStruct->first();
  EXPECT_EQ("1", itStruct->currentItem()->symbol());
  itStruct->next();
  ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
  EXPECT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_EQ("Y", itStruct->currentItem()->symbol());
  ASSERT_FALSE(itStruct->isDone());
  itStruct->next();
  ASSERT_TRUE(itStruct->isDone());

  Iterator<Term *> * itStruct2 = t.createIterator();
  itStruct2->first();
  EXPECT_EQ("X", itStruct2->currentItem()->symbol());
  EXPECT_FALSE(itStruct2->isDone());
  itStruct2->next();
  EXPECT_EQ("2", itStruct2->currentItem()->symbol());
  EXPECT_FALSE(itStruct2->isDone());
  itStruct2->next();
  EXPECT_TRUE(itStruct2->isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term *> * itList = l.createIterator();
    itList->first();
    ASSERT_EQ("1", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
    ASSERT_FALSE(itList->isDone());
    itList->next();
    ASSERT_EQ("Y", itList->currentItem()->symbol());
    itList->next();
    ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  Iterator <Term *> * it1 = one.createIterator();
  it1 -> first();
  ASSERT_TRUE(it1->isDone());
  Iterator <Term *> * it2 = one.createIterator();
  it2 -> first();
  ASSERT_TRUE(it2->isDone());
}
TEST(iterator, structDFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term *> * itStruct = s.createDFSIterator();
  itStruct -> first();
  EXPECT_EQ("1", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("t(X, 2)", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("X", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("2", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("Y", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_TRUE(itStruct -> isDone());
}

TEST(iterator, structDFSIterator2){
  Number one(1);
  Atom tom("tom");
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct u(Atom("u"), {&tom, &Y});
  Struct t(Atom("t"), { &X, &two, &one});
  Struct z(Atom("z"), { &one, &t, &two , &u});
  Iterator<Term *>* itStruct = z.createDFSIterator();
  itStruct -> first();
  EXPECT_EQ("1", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("t(X, 2, 1)", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("X", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("2", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("1", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("2", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("u(tom, Y)", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("tom", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("Y", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_TRUE(itStruct -> isDone());
}
TEST(iterator, listtDFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List list({ &X, &two });
  List list2({ &one, &list, &Y });
  Iterator<Term *> * itList = list2.createDFSIterator();
  itList -> first();
  EXPECT_EQ("1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[X, 2]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("X", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("Y", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_TRUE(itList -> isDone());
}

TEST(iterator, listtDFSIterator2){
  Number one(1);
  Atom tom("tom");
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List list1({&tom, &Y});
  List list2({ &X, &two });
  List list3({ &one, &list2, &two, &list1 });
  Iterator<Term *> * itList = list3.createDFSIterator();
  itList -> first();
  EXPECT_EQ("1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[X, 2]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("X", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[tom, Y]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("tom", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("Y", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_TRUE(itList -> isDone());
}

TEST(iterator, structBFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  Iterator<Term *> * itStruct = s.createBFSIterator();
  itStruct -> first();
  EXPECT_EQ("1", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("t(X, 2)", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("Y", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("X", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("2", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_TRUE(itStruct -> isDone());
}

TEST(iterator, structBFSIterator2){
  Number one(1);
  Atom tom("tom");
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct u(Atom("u"), {&tom, &Y});
  Struct t(Atom("t"), { &X, &two, &one});
  Struct z(Atom("z"), { &one, &t, &two , &u});
  Iterator<Term *> * itStruct = z.createBFSIterator();
  itStruct -> first();
  EXPECT_EQ("1", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("t(X, 2, 1)", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("2", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("u(tom, Y)", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("X", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("2", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("1", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("tom", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_EQ("Y", itStruct -> currentItem() -> symbol());
  itStruct -> next();
  EXPECT_TRUE(itStruct -> isDone());
}

TEST(iterator, listtBFSIterator){
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List list1({ &X, &two });
  List list2({ &one, &list1, &Y });
  Iterator<Term *> * itList = list2.createBFSIterator();
  itList -> first();
  EXPECT_EQ("1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[X, 2]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("Y", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("X", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_TRUE(itList -> isDone());
}

TEST(iterator, listtBFSIterator2){
  Number one(1);
  Atom tom("tom");
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List list1({&tom, &Y});
  List list2({ &X, &two });
  List list3({ &one, &list2, &two, &list1 });
  Iterator<Term *> * itList = list3.createBFSIterator();
  itList -> first();
  EXPECT_EQ("1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[X, 2]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[tom, Y]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("X", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("tom", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("Y", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_TRUE(itList -> isDone());
}
TEST(iterator, listtDFSIterator3){
  Number one(1);
  Atom tom("tom");
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  List list1({ &tom, &Y});
  List list2({ &X, &list1 });
  List list3({ &one, &list2});
  List list4({ &list1, &one, &list3});
  Iterator<Term *> * itList = list4.createDFSIterator();
  itList -> first();
  EXPECT_EQ("[tom, Y]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("tom", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("Y", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[1, [X, [tom, Y]]]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[X, [tom, Y]]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("X", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[tom, Y]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("tom", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("Y", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_TRUE(itList -> isDone());
}

TEST(iterator, structlisttDFSIterator){
  Number one(1);
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom sauce("sauce");
  Atom cheese("cheese");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List list1({&pickleSlice1, &pickleSlice2});
  List list2({ &onion1, &onion2 });
  Struct bigMac(Atom("bigMac"), {&bun, &beefPatty, &shreddedLettuce, &sauce, &cheese, &list1, &list2});
  List list3({ &fries1, &fries2});
  Struct combo1(Atom("combo1"), {&bigMac, &coke, &list3});

  Iterator<Term *> * itList = combo1.createDFSIterator();
  itList -> first();
  EXPECT_EQ("bigMac(bun, beefPatty, shreddedLettuce, sauce, cheese, [pickleSlice1, pickleSlice2], [onion1, onion2])", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("bun", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("beefPatty", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("shreddedLettuce", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("sauce", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("cheese", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[pickleSlice1, pickleSlice2]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("pickleSlice1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("pickleSlice2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[onion1, onion2]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("onion1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("onion2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("coke", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("[fries1, fries2]", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("fries1", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_EQ("fries2", itList -> currentItem() -> symbol());
  itList -> next();
  EXPECT_TRUE(itList -> isDone());
}

#endif
