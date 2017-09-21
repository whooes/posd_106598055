// list::sort
#include "include/Sort.h"

// comparison
bool sortByIncreasingPerimeterCMP(Shape * shapes1, Shape * shapes2)
{
	return (shapes1->perimeter() < shapes2->perimeter());
}

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapes) {
	shapes->sort(sortByIncreasingPerimeterCMP);
}

bool sortByDecreasingPerimeterCMP(Shape * shapes1, Shape * shapes2)
{
	return (shapes1->perimeter() > shapes2->perimeter());
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapes) {
	shapes->sort(sortByDecreasingPerimeterCMP);
}

bool sortByIncreasingAreaCMP(Shape * shapes1, Shape * shapes2)
{
	return (shapes1->area() < shapes2->area());
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapes) {
	shapes->sort(sortByIncreasingAreaCMP);
}

bool sortByDecreasingAreaCMP(Shape * shapes1, Shape * shapes2)
{
	return (shapes1->area() > shapes2->area());
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapes) {
	shapes->sort(sortByDecreasingAreaCMP);
}

bool sortByIncreasingCompactnessCMP(Shape * shapes1, Shape * shapes2)
{
	return (shapes1->compactness() < shapes2->compactness());
}
void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapes) {
	shapes->sort(sortByIncreasingCompactnessCMP);
}