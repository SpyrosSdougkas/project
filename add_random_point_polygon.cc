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
#include "check_black_lines.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef Polygon_2::Edge_const_iterator EdgeIterator;
typedef std::vector<Point_2> Convex_hull_points;
typedef CGAL::Convex_hull_traits_adapter_2<K,
                                           CGAL::Pointer_property_map<Point_2>::type>
    Convex_hull_traits_2;
typedef K::Segment_2 Segment_2;
typedef K::Line_2 Line_2;
typedef K::Intersect_2 Intersect_2;

CGAL::Polygon_2<K> addpointtopolygon(Polygon_2 polygon, std::vector<K::Segment_2> conline, K::Point_2 point)
{

    std::vector<K::Segment_2> maybe, maybe1, red, redlines, seg;
    K::Point_2 arxi, telos;
    int handler = 0, place = 0, n = 0;

    for (K::Segment_2 seg : conline)
    {
        handler = 0;
        arxi = seg.source();
        telos = seg.target();
        Segment_2 seg1(point, arxi);
        Segment_2 seg2(point, telos);
        for (K::Segment_2 check : conline)
        {
            if (seg != check &&
                !(CGAL::collinear(arxi, check.source(), check.target()) &&
                  CGAL::collinear(arxi, check.source(), check.target())))
            {
                const auto re = intersection(seg1, check);
                if (re)
                {

                    const Point_2 *p = boost::get<Point_2>(&*re);

                    std::cout << *p << std::endl;
                    if (*p != arxi)
                    {
                        handler = 1;
                    }
                }
            }
        }
        if (handler == 0)
        {
            maybe.push_back(seg);
        }
    }

    for (K::Segment_2 seg : maybe)
    {
        handler = 0;
        arxi = seg.source();
        telos = seg.target();
        Segment_2 seg1(point, arxi);
        Segment_2 seg2(point, telos);

        for (K::Segment_2 check : conline)
        {
            if (seg != check)
            {
                const auto re = intersection(seg2, check);
                if (re)
                {
                    const Point_2 *p = boost::get<Point_2>(&*re);
                    if (*p != telos)
                    {
                        handler = 1;
                    }
                }
            }
        }
        if (handler == 0)
        {
            maybe1.push_back(seg);
        }
    }

    handler = 0;

    for (K::Segment_2 seg : maybe1)
    {
        handler = 0;
        arxi = seg.source();
        telos = seg.target();
        Segment_2 seg1(point, CGAL::midpoint(arxi, telos));

        for (K::Segment_2 check : conline)
        {
            if (seg != check)
            {
                const auto re = intersection(seg1, check);
                if (re)
                {
                    const Point_2 *p = boost::get<Point_2>(&*re);
                    if (*p != telos)
                    {
                        handler = 1;
                    }
                }
            }
        }
        if (handler == 0)
        {
            red.push_back(seg);
        }
    }

    for (K::Segment_2 i : red)
    {
        std::cout << i << "\n";
        std::cout << i.max() << "   " << i.min() << "   " << CGAL::midpoint(i.max(), i.min()) << "\n";

        std::cout << "\n";
    }

    std::vector<K::Segment_2> redconpoly;
    std::vector<K::Segment_2> redpoly, limit;
    bool orient = polygon.is_clockwise_oriented();
    int find = 0, hidelines = 0;

    for (K::Segment_2 redline : red)
    {
        handler = 1;
        n = 0;
        std::cout << "red edges:  " << redline << std::endl;
        for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
        {
            if ((redline == *ei) || redline.opposite() == *ei)
            {
                place = n + 1;
                handler = 0;
                limit.push_back(redline);
            }
            n++;
        }
        if (handler == 1)
        {
            redpoly.push_back(redline);
            hidelines = 1;
        }
    }

    if (hidelines == 1)
    {

        std::vector<K::Segment_2> blackline;

        if (orient == 0)
        {

            for (K::Segment_2 redline : redpoly)
            {
                n = 0;
                for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
                {

                    if (redline.source() == polygon.vertex(n))
                    {
                        find = 1;
                    }
                    if (find == 1)
                    {
                        if (redline.target() == polygon.vertex(n))
                        {
                            find = 0;
                            break;
                        }
                        blackline.push_back(*ei);
                    }
                    n++;
                }
            }
        }
        if (orient == 1)
        {
            polygon.reverse_orientation();
            for (K::Segment_2 redline : redpoly)
            {
                n = 0;
                for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
                {

                    if (redline.source() == polygon.vertex(n))
                    {
                        find = 1;
                    }
                    if (find == 1)
                    {
                        if (redline.target() == polygon.vertex(n))
                        {
                            find = 0;
                            break;
                        }
                        blackline.push_back(*ei);
                    }
                    n++;
                }
            }
        }
        for (K::Segment_2 redline : blackline)
        {
            limit.push_back(redline);
        }

        blackline = checkblacklines(blackline, limit, point);
        std::cout << "autes einai oi orates akmes" << std::endl;

        for (K::Segment_2 black : blackline)
        {
            n = 0;
            std::cout << black << std::endl;
            for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
            {
                if ((black == *ei) || black.opposite() == *ei)
                {
                    place = n + 1;
                    handler = 1;
                }
                n++;
            }
        }
    }
    std::cout << std::endl;
    polygon.insert(polygon.begin() + place, point);
    n = 0;
    for (EdgeIterator ei = polygon.edges_begin(); ei != polygon.edges_end(); ++ei)
        std::cout << "edge " << n++ << " = " << *ei << std::endl;

    return polygon;
};
