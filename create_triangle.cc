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

// std::vector <K::Segment_2> findrededges ( K::Point_2 P, )
std::vector <K::Point_2> findpoints (std::vector<K::Point_2> pointslist){
    std::vector <K::Point_2> newlist;
    if( !(CGAL::collinear(K::Point_2(pointslist[0]), K::Point_2(pointslist[1]), K::Point_2(pointslist[2])))){
        // std::cout << "they are not collinear" << std::endl;
        for (int i=0; i < 3; i++){   
            newlist.push_back(pointslist.at(i));
        }     
    }
    else{
        for (int i=3; i < pointslist.size(); i++){  
            if( (CGAL::collinear(K::Point_2(pointslist[0]), K::Point_2(pointslist[i-1]), K::Point_2(pointslist[i])))){
                std::cout << "they are not collinear" << std::endl;
                newlist.push_back(pointslist.at(i));
                break;  
            }
            else{
                newlist.push_back(pointslist.at(i));
            }
        }        
    }
// std::cout << "they are not collinear" << std::endl;
    return newlist;
}

CGAL::Polygon_2<K> createtriangle (std::vector<K::Point_2> pointslist){
    Polygon_2 polygon;
    for(int i=0; i<pointslist.size(); i++){
        polygon.insert(polygon.begin()+i,pointslist.at(i));
    }
    int n=0;
    std::cout<<"This the polygon triangle:\n";   
    for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
        std::cout << "edge " << n++ << " = " << *ei << std::endl;  
    return polygon;
};