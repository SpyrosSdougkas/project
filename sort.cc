#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                         Point_2;

bool decreasing_x(Point_2 p1, Point_2 p2){      
    return (p1.x() > p2.x());
}

bool increasing_x(Point_2 p1, Point_2 p2){
    return (p1.x() < p2.x());
}

bool decreasing_y(Point_2 p1, Point_2 p2){
    return (p1.y() > p2.y());
}

bool increasing_y(Point_2 p1, Point_2 p2){
    return (p1.y() < p2.y());
}

std::vector <K::Point_2> pointsortfun(std::vector<K::Point_2> pointvector, char *str){
    if (strcmp(str ,"1a") == 0){
        std::sort (pointvector.begin(), pointvector.end(),decreasing_x);
        for (K::Point_2 i: pointvector){
            std::cout << i << ' ';
        }
    }
    if (strcmp(str ,"1b") == 0){
        std::sort (pointvector.begin(), pointvector.end(),increasing_x);
        for (K::Point_2 i: pointvector){
            std::cout << i << ' ';
        }      
    }
    if (strcmp(str ,"2a") == 0){
    std::sort (pointvector.begin(), pointvector.end(),decreasing_y);  
        for (K::Point_2 i: pointvector){
            std::cout << i << ' ';
        }            
    }
    if (strcmp(str ,"2b") == 0){
    std::sort (pointvector.begin(), pointvector.end(),increasing_y);   
        for (K::Point_2 i: pointvector){
            std::cout << i << ' ';
        }            
    }
    std::cout<<"\n";
    for (K::Point_2 i: pointvector){
        std::cout << i << ' ';
    }
    return pointvector;
}