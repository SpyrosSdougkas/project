#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                         Point_2;

bool decreasing_x(Point_2 , Point_2 );
bool increasing_x(Point_2 , Point_2 );
bool decreasing_y(Point_2 , Point_2 );
bool increasing_y(Point_2 , Point_2 );
std::vector <K::Point_2> pointsortfun(std::vector<K::Point_2> , char *);