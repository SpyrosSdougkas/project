#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <vector>
#include <cassert>
#include <list>
#include <set>
#include <CGAL/Arrangement_2.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>
#include <CGAL/Polyline_simplification_2/simplify.h>
#include <CGAL/Polyline_simplification_2/Squared_distance_cost.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/intersections.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                         Point_2;
typedef CGAL::Polygon_2<K>                                  Polygon_2;
typedef Polygon_2::Edge_const_iterator EdgeIterator;
typedef Polygon_2::Vertex_const_iterator VertexIterator;
typedef std::vector <Point_2> Convex_hull_points;
typedef CGAL::Convex_hull_traits_adapter_2<K,
CGAL::Pointer_property_map<Point_2>::type > Convex_hull_traits_2;
typedef K::Segment_2 Segment_2;
typedef K::Line_2 Line_2;
typedef K::Intersect_2 Intersect_2;
typedef CGAL::Simple_cartesian<double> Kernel;



CGAL::Polygon_2<K>  addnewpoint(Polygon_2 polygon, std::vector <K::Point_2> points);