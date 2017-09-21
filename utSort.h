#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include "gtest/gtest.h"

 TEST (Sort, sortByIncreasingPerimeter) {
	Rectangle rec = Rectangle(1.0, 1.0, 1, 1, "r");
	vertex v1 = { 2.0,1.0 };
	vertex v2 = { 1.0,1.0 };
	vertex v3 = { 0.0,0.0 };
	Triangle tri = Triangle(v1, v2, v3, "t");
	Circle cir = Circle(1.0, 0.0, 1.0, "r");
	std::list<Shape*> shapes;
	shapes.push_back(&tri);
	shapes.push_back(&rec);
	shapes.push_back(&cir);
	Sort::sortByIncreasingPerimeter(&shapes); 

	std::list<Shape*>::iterator itr;
	itr = shapes.begin();

	ASSERT_EQ(&rec, *itr);
	itr++;// compare the address
	ASSERT_EQ(&tri, *itr);
	itr++;
	ASSERT_EQ(&cir, *itr);

}

 TEST (Sort, sortByDecreasingPerimeter) {
	Rectangle rec = Rectangle(1.0, 1.0, 1, 1, "r");
	vertex v1 = { 2.0,1.0 };
	vertex v2 = { 1.0,1.0 };
	vertex v3 = { 0.0,0.0 };
	Triangle tri = Triangle(v1, v2, v3, "t");
	Circle cir = Circle(1.0, 0.0, 1.0, "r");
	std::list<Shape*> shapes;
	shapes.push_back(&tri);
	shapes.push_back(&rec);
	shapes.push_back(&cir);
	Sort::sortByDecreasingPerimeter(&shapes);
	std::list<Shape*>::iterator itr;
	itr = shapes.begin();

	ASSERT_EQ(&cir, *itr);
	itr++;// compare the address
	ASSERT_EQ(&tri, *itr);
	itr++;
	ASSERT_EQ(&rec, *itr);
}

 TEST(Sort, sortByIncreasingArea) {
	Rectangle rec = Rectangle(1.0, 1.0, 1, 1);
	vertex v1 = { 2.0,1.0 };
	vertex v2 = { 1.0,1.0 };
	vertex v3 = { 0.0,0.0 };
	Triangle tri = Triangle(v1, v2, v3);
	Circle cir = Circle(1.0, 0.0, 1.0);
	std::list<Shape*> shapes;
	shapes.push_back(&tri);
	shapes.push_back(&rec);
	shapes.push_back(&cir);
	Sort::sortByIncreasingArea(&shapes);
	std::list<Shape*>::iterator itr;
	itr = shapes.begin();

	ASSERT_EQ(&tri, *itr);
	itr++;// compare the address
	ASSERT_EQ(&rec, *itr);
	itr++;
	ASSERT_EQ(&cir, *itr);
}
 TEST (Sort, sortByDecreasingArea) {
	Rectangle rec = Rectangle(1.0, 1.0, 1, 1);
	vertex v1 = { 2.0,1.0 };
	vertex v2 = { 1.0,1.0 };
	vertex v3 = { 0.0,0.0 };
	Triangle tri = Triangle(v1, v2, v3);
	Circle cir = Circle(1.0, 0.0, 1.0);
	std::list<Shape*> shapes;
	shapes.push_back(&cir);
	shapes.push_back(&rec);
	shapes.push_back(&tri);
	Sort::sortByDecreasingArea(&shapes);
	std::list<Shape*>::iterator itr;
	itr = shapes.begin();

	ASSERT_EQ(&cir, *itr);
	itr++;// compare the address
	ASSERT_EQ(&rec, *itr);
	itr++;
	ASSERT_EQ(&tri, *itr);
}

 TEST (Sort, sortByIncreasingCompactness) {
	Rectangle rec = Rectangle(1.0, 1.0, 1, 1);
	vertex v1 = { 2.0,1.0 };
	vertex v2 = { 1.0,1.0 };
	vertex v3 = { 0.0,0.0 };
	Triangle tri = Triangle(v1, v2, v3);
	Circle cir = Circle(1.0, 0.0, 1.0);
	std::list<Shape*> shapes;
	shapes.push_back(&tri);
	shapes.push_back(&rec);
	shapes.push_back(&cir);
	Sort::sortByIncreasingCompactness(&shapes);
	std::list<Shape*>::iterator itr;
	itr = shapes.begin();

	ASSERT_EQ(&tri, *itr);
	itr++;// compare the address
	ASSERT_EQ(&rec, *itr);
	itr++;
	ASSERT_EQ(&cir, *itr);
}

#endif
