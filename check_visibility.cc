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


int checkvisibility (Polygon_2 polygon,K::Segment_2  seg, K::Point_2 point){
    std::vector <K::Segment_2> maybe,maybe1, red;
    K::Segment_2 poledge;
    K::Point_2 arxi,telos;
    int handler=0,place=0,n=0,control1=0, control2=0, control3=0;
    handler=0;
    arxi=seg.source();
    telos=seg.target();
    Segment_2 seg1(point, arxi);
    Segment_2 seg2(point, telos);
    for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei){
        poledge=polygon.edge(n);
        if ( !(seg==poledge || seg==poledge.opposite() )&&
            !(CGAL::collinear(point, poledge.source(), poledge.target()))                     
        ){
            const auto re = intersection( seg1,poledge);
            if(re){
                    const Point_2* p = boost::get<Point_2 >(&*re);
                    if (*p!=arxi){
                        handler=1;
                    }
            }
        }
        n++;
    }
    if (handler==0){
        control1=1;
    }
    n=0;
    if(control1==1){
        handler=0;
        arxi=seg.source();
        telos=seg.target();
        Segment_2 seg1(point, arxi);
        Segment_2 seg2(point, telos);
        for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei){
            poledge=polygon.edge(n); 
            if ( !(seg==poledge || seg==poledge.opposite() )&&
                !(CGAL::collinear(point, poledge.source(), poledge.target()))                   
            ){
                const auto re = intersection( seg2,poledge);
                if(re){                             
                    const Point_2* p = boost::get<Point_2 >(&*re);
                    if (*p!=telos){
                        handler=1;
                    }
                }
            }
            n++;
        }
        if (handler==0){
            control2=1;
        }
    }

    n=0;
    if(control2==1){
        handler=0;
        arxi=seg.source();
        telos=seg.target();
        Segment_2 seg1(point, CGAL::midpoint(arxi,telos));
        for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei){
            poledge=polygon.edge(n);
            if ( !(seg==poledge || seg==poledge.opposite() )&&
                !(CGAL::collinear(point, poledge.source(), poledge.target()))                     
            ){
                const auto re = intersection( seg1,poledge);
                if(re){                             
                    const Point_2* p = boost::get<Point_2 >(&*re);
                    if (*p!=telos){
                        handler=1;
                    }
                }
            }
            n++;
        }
        if (handler==0){
            control3=1;
        }
    }

    if (control3==1){
        return 1;
    }
    else{
        return 0;
    }
}
