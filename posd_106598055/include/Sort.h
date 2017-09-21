#include <list>
#include "Shapes.h"

class Sort {

  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapes);

  public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapes);

  public :static void sortByIncreasingArea(std::list<Shape *> * shapes);

  public :static void sortByDecreasingArea(std::list<Shape *> * shapes);
  
  public :static void sortByIncreasingCompactness(std::list<Shape *> * shapes);
  
};
