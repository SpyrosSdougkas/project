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

#include "sort.h"
#include "find_points_from_file.h"
#include "create_triangle.h"
#include "create_convex.h"
#include "add_random_point_polygon.h"
#include "add_min_max_point_polygon.h"
#include "add_point_convex.h"

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
 
 
void incremental_algorithm(char **argv){
    std::vector < K::Point_2 > pointvector;
    std::ifstream myfile (argv[2]);

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
    std::cout<<"\n";
    pointvector=pointsortfun(pointvector,argv[3]);
    std::cout<<"\n";
    //ftiaxno to trigono


    std::vector <K::Point_2> pointlist=findpoints(pointvector);
    Polygon_2 polygon=createtriangle(pointlist);
    std::cout<<"\n";

    // ////// ftiaxno to kirto periblima

    std::vector <K::Segment_2>  conline=findconvex(pointlist);
    std::cout<<"\n";

    ////// prostheto point
    std::vector <K::Segment_2> maybe,red, redlines, seg;
    K::Point_2 point,arxi,telos;
    int handler;
    for (int i=3; i < pointvector.size(); i++){   
        // polygon.push_back(pointvecror.at(i));
        point=pointvector.at(i);
        pointlist.push_back(point);
        if (strcmp(argv[4],"1")==0){
            polygon=addpointtopolygon(polygon,conline,point);
        }
        else{
            polygon=addpointtopolygonminmax(polygon,conline,point, argv[3]);
        }
        conline.clear();
        conline=addpointtoconvex(pointlist);
        std::cout<<"\n";       
    }
    std::cout << "The polygon is " <<
    (polygon.is_simple() ? "" : "not ") << "simple." << std::endl;

}