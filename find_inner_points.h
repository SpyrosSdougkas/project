#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                         Point_2;

std::vector <K::Point_2> findinnerpoints(std::vector <K::Point_2>points);