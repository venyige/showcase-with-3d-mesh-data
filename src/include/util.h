#ifndef UTIL_H
#define UTIL_H
#include<Eigen/Dense>


namespace tcmu_util{

typedef struct trPar{
    std::string cmd;
    Eigen::Vector3d vec;
    double num;
} trPar;

//REF.:
//2D „pt in triangle” fiddle with multiplication-only solution
//http://jsfiddle.net/PerroAZUL/zdaY8/1/
inline bool ptInTriangle(Eigen::Vector3d& p, Eigen::Vector3d& p0, Eigen::Vector3d& p1, Eigen::Vector3d& p2) {
    double A = .5 * (-p1.y() * p2.x() + p0.y() * (-p1.x() + p2.x()) + p0.x() * (p1.y() - p2.y()) + p1.x() * p2.y());
    double s;
    double t;
    if(std::signbit(A)){
        s = -(p0.y() * p2.x() - p0.x() * p2.y() + (p2.y() - p0.y()) * p.x() + (p0.x() - p2.x()) * p.y()) ;
        t = -(p0.x() * p1.y() - p0.y() * p1.x() + (p0.y() - p1.y()) * p.x() + (p1.x() - p0.x()) * p.y()) ;
    }else{
        s = (p0.y() * p2.x() - p0.x() * p2.y() + (p2.y() - p0.y()) * p.x() + (p0.x() - p2.x()) * p.y()) ;
        t = (p0.x() * p1.y() - p0.y() * p1.x() + (p0.y() - p1.y()) * p.x() + (p1.x() - p0.x()) * p.y()) ;
    }
    return s > 0. && t > 0. && (s + t) < 2. * abs(A);
}

// Python-"in"-ish
//    auto result = std::find(std::begin(v), std::end(v), arg);
//    if (result != std::end(v)){}
};

#endif // UTIL_H
