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

void based_on_KP(char **argv){
    std::vector < K::Point_2 > pointvector;
    std::vector < K::Point_2 > innerpoints;
    std::ifstream myfile (argv[2]);
    int n = 0;
    if ( myfile.is_open() ){
        int mychar;
        char ch;
        std::string str, str1m, str2;
        std::stringstream ss;
            while ( std::getline(myfile,str)){
                if ( str.at(0) != '#' )
                    pointvector.push_back(createpointlist(str));
            }
    }
    for (K::Point_2 i: pointvector){
        std::cout << i << ' ';
    }
    Polygon_2 polygon;
    polygon=find_convex_points(polygon,pointvector);
    std::cout<<"first pol: "<<std::endl;
    for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
    std::cout << "edge " << n++ << " = " << *ei << std::endl;
    innerpoints=findinnerpoints(pointvector);
    std::cout<<"innerpoints: "<<std::endl;   
    for (K::Point_2 i : innerpoints){
         std::cout << i<<"  "<<"\n" ;
    
    }
    std::cout<<"\n";
    int pointsnum= innerpoints.size();
    for (int k=0; k<pointsnum; k++){
        if((strcmp(argv[3],"1"))==0)
        polygon=addnewpoint(polygon,innerpoints);

        if(strcmp(argv[3],"2")==0)
        polygon=addnewpointminmax(polygon,innerpoints,argv[2]);

        if(strcmp(argv[3],"3")==0)
        polygon=addnewpointminmax(polygon,innerpoints,argv[2]);

        n=0;
        for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
        std::cout << "edge " << n++ << " = " << *ei << std::endl;
        innerpoints=findnewpoints(pointvector,polygon);
        std::cout<<"innerpoints: "<<std::endl;
        if (innerpoints.size()==0){
            std::cout<<"No more innerpoints!!! "<<std::endl;
        }
        else{
            for (K::Point_2 i : innerpoints){
                std::cout << i<<"  "<<"\n" ;
            }  
        }
        std::cout << "The polygon is " <<
        (polygon.is_simple() ? "" : "not ") << "simple." << std::endl;   
    }
    std::cout<<"Area of polygon -> "<< polygon.area()<<std::endl;
}