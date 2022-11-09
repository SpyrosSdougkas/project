#include <iostream>
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

#include "find_points_from_file.h"
#include "find_convex_points.h"
#include "find_inner_points.h"
#include "add_new_points.h"
#include "find_new_points.h"
#include "add_new_point_min_max.h"

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

std::vector <K::Point_2> findinnerpoints(std::vector <K::Point_2>points){
    Convex_hull_points  result;
    std::vector < K::Point_2 > innerpoints;
    int handler=0;
    CGAL::convex_hull_2( points.begin(), points.end(), back_inserter(result) ); 
    std::cout<<"\n";   
    for (K::Point_2 j : points){
        for(int i = 0 ; i < result.size();i++){
            if ( j==result[i]){
                handler=1;
            }
        }
        if (handler==0){
            innerpoints.push_back(j);
            handler=1;
        }
        handler=0;
    }  
    return innerpoints;
}