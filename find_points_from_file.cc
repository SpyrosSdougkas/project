#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                         Point_2;

K::Point_2 createpointlist( std::string s ){
    std::vector < K::Point_2 >  v ;
    K::Point_2::Rep p;
    std::stringstream ss;
    ss << s;
    std::string temp;
    int tein, a,b;
    char tech;
    while(!ss.eof()) {
        ss>> temp;                                      //take words into temp_str one by one
        if(std::stringstream(temp) >> tein) {           //try to convert string to int
            ss>> a;
            ss>> b;     
            v.push_back(p);
        }
        else if (std::stringstream(temp) >> tech) {     //try to convert string to int
            break;
        } 
        temp = "";                                      //clear temp string
    }  
    return Point_2(a,b);
};