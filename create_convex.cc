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
typedef std::vector <Point_2> Convex_hull_points;
typedef CGAL::Convex_hull_traits_adapter_2<K,
CGAL::Pointer_property_map<Point_2>::type > Convex_hull_traits_2;
typedef K::Segment_2 Segment_2;
typedef K::Line_2 Line_2;
typedef K::Intersect_2 Intersect_2;


std::vector < K::Segment_2> findconvex ( std::vector <K::Point_2> convex_hull_points){
    Convex_hull_points  result;

    CGAL::convex_hull_2( convex_hull_points.begin(), convex_hull_points.end(), std::back_inserter(result) );
    std::cout << result.size() << " points on the convex hull" << std::endl;
    std::vector <K::Segment_2> conline;

    for(int i = 0; i < result.size(); i++){
        if ( i<= result.size() - 2){
            conline.push_back( Segment_2(result[i],result[i+1]));
        }
        if ( i == result.size() - 1){
            conline.push_back( Segment_2(result[i],result[0]));
        }
    }
    std::cout << "This is the convex  "<< std::endl;

    for (K::Segment_2 i : conline){
         std::cout << i ;
          std::cout<<"\n";       
    }
    std::cout << "This is the convex  "<< std::endl;
    return conline;
}