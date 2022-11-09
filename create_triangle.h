#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                  Point_2;
typedef CGAL::Polygon_2<K>          Polygon_2;
typedef Polygon_2::Edge_const_iterator EdgeIterator;

std::vector <K::Point_2> findpoints (std::vector<K::Point_2> );
CGAL::Polygon_2<K> createtriangle (std::vector<K::Point_2> );