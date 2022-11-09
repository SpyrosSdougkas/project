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

#include "check_visibility.h"
#include "pair.h"

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

CGAL::Polygon_2<K>  addnewpoint(Polygon_2 polygon, std::vector <K::Point_2> points){

    double dist, newdist;
    int n=0, handler=0, check=0;
    pair p;
    std::vector <pair> pairvector;
    for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei){
        for(K::Point_2 j : points){
            if (handler==0){
                check=checkvisibility(polygon,*ei,j);
                if (check==1)
                    {p.seg=*ei;
                    p.point=j;
                    p.dist=CGAL::squared_distance(*ei,j);
                    handler=1;
                    p.place=n;
                    }
            }
            else{
                check=checkvisibility(polygon,*ei,j);
                if (check==1){
                    newdist=CGAL::squared_distance(*ei,j);
                    if(p.dist>newdist){
                        p.dist=newdist;
                        p.point=j;
                        p.seg=*ei;
                        p.place=n;
                    }
                }
            }
            dist = CGAL::squared_distance(*ei,j);
            std::cout <<"dist from edge "<< n<<"   "<< *ei<< " to "<< j <<" is "<< dist<<"\n" ;
        }
        if (handler==0){
            std::cout <<"no visibly points for this edge"<<"\n" ;
        }
        else{
            std::cout <<"min dist is from "<< p.seg<< " to "<< p.point <<" is "<< p.dist<<"\n" ;
            pairvector.push_back(p);
        }
        handler=0;
        n++;
    }
    std::cout<<"\n";
    pair p1;
    p1=pairvector[0];
    std::cout <<"no -------------- points for this edge"<<"\n" ;
    for (int i=0; i<pairvector.size(); i++){
        if(p1.dist>=pairvector[i].dist){
            p1=pairvector[i];
        }
    }
    std::cout <<"insert point "<< p1.point<<" at place "<< p1.place<<"  for edgge  "<<p1.seg<<"\n" ;
    polygon.insert(polygon.begin()+p1.place+1,p1.point);

    return polygon;
}