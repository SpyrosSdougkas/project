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

std::vector < K::Segment_2> checkblacklines
 ( std::vector <K::Segment_2> blacklines,std::vector <K::Segment_2>  limit, K::Point_2 point){

    std::vector <K::Segment_2> maybe,red, redlines, seg, bl;
    K::Point_2 arxi,telos;
    int handler=0,place=0,n=0;
    for (K::Segment_2 seg : limit){
        handler=0;
        arxi=seg.source();
        telos=seg.target();
        Segment_2 seg1(point, arxi);
        Segment_2 seg2(point, telos);
        for ( K::Segment_2 check : limit){
            if ( seg!=check){
                const auto re = intersection( seg1,check);
                if(re){
                    const Point_2* p = boost::get<Point_2 >(&*re);
                    if (*p!=arxi && *p!=telos){
                        handler=1;
                    }
                }
            }
        }
        if (handler==0){
            maybe.push_back(seg);
        }
    }
    handler=0;
    for (K::Segment_2 seg : maybe){
        handler=0;
        arxi=seg.source();
        telos=seg.target();
        Segment_2 seg1(point, arxi);
        Segment_2 seg2(point, telos);
        for ( K::Segment_2 check : limit){
            if ( seg!=check){
                const auto re = intersection( seg2,check);
                if(re){    
                    const Point_2* p = boost::get<Point_2 >(&*re);
                    if (*p!=telos && *p!=arxi ){
                        handler=1;
                    }
                }
            }
        }
        if (handler==0){
            bl.push_back(seg);
        }
    }
    for (K::Segment_2 i : bl){
        std::cout << "visibly edges:  "<<i<<"\n";       
    }
    return bl;
}