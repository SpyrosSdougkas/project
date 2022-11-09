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

#include "pair.h"
#include "check_visibility.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef Polygon_2::Edge_const_iterator EdgeIterator;
typedef Polygon_2::Vertex_const_iterator VertexIterator;
typedef std::vector<Point_2> Convex_hull_points;
typedef CGAL::Convex_hull_traits_adapter_2<K,
                                           CGAL::Pointer_property_map<Point_2>::type>
    Convex_hull_traits_2;
typedef K::Segment_2 Segment_2;
typedef K::Line_2 Line_2;
typedef K::Intersect_2 Intersect_2;
typedef CGAL::Simple_cartesian<double> Kernel;

CGAL::Polygon_2<K> addnewpointminmax(Polygon_2 polygon, std::vector<K::Point_2> points, char *option)
{

    double dist, newdist;
    int n = 0, handler = 0, check = 0;
    pair p;
    std::vector<pair> pairvector;
    for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
    {
        for (K::Point_2 j : points)
        {

            check = checkvisibility(polygon, *ei, j);
            if (check == 1)
            {
                p.seg = *ei;
                p.point = j;
                std::cout << "no visibly points for this edge"
                          << "\n";
                p.dist = CGAL::squared_distance(*ei, j);
                handler = 1;
                p.place = n;
                pairvector.push_back(p);
                std::cout << "min dist is from " << p.seg << " to " << p.point << " is " << p.dist << "\n";
            }

            dist = CGAL::squared_distance(*ei, j);
            std::cout << "dist from edge " << n << "   " << *ei << " to " << j << " is " << dist << "\n";
        }
        if (handler == 0)
        {
            std::cout << "no visibly points for this edge"
                      << "\n";
        }
        handler = 0;
        n++;
    }

    std::cout << "point q is   " << pairvector.size();
    int IsInside;
    std::cout << "point q is";

    std::cout << "\n";

    std::cout << "point q is";

    std::vector<CGAL::Polygon_2<K>> temppolygonlist;

    std::cout << "point q is";
    Polygon_2 temppol;
    pair p1;
    int inouthandler = 0;
    for (int i = 0; i < pairvector.size(); i++)
    {
        inouthandler = 0;
        temppol = polygon;
        std::cout << "point q is";
        std::cout << "insert point " << pairvector[i].point << " at place " << pairvector[i].place + 1 << "  for edgge  " << pairvector[i].seg << "\n";
        temppol.insert(temppol.begin() + pairvector[i].place + 1, pairvector[i].point);
        for (K::Point_2 j : points)
        {
            if (pairvector[i].point != j)
            {

                bool IsInside = (temppol.bounded_side(j) == CGAL::ON_BOUNDED_SIDE);
                std::cout << "point q is";
                if (!IsInside)
                {

                    inouthandler = 1;
                }
            }
        }

        if (inouthandler == 0)
        {
            temppolygonlist.push_back(temppol);
        }

    }

    temppol = temppolygonlist[0];

    if ((strcmp(option, "2")) == 0)
        for (int i = 1; i < temppolygonlist.size(); i++)
        {
            if (temppol.area() > temppolygonlist[i].area())
            {
                temppol = temppolygonlist[i];
            }
        }

    if ((strcmp(option, "3")) == 0)
        for (int i = 1; i < temppolygonlist.size(); i++)
        {
            if (temppol.area() < temppolygonlist[i].area())
            {
                temppol = temppolygonlist[i];
            }
        }

    return temppol;
}
