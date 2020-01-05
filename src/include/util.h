#ifndef UTIL_H
#define UTIL_H
#include<Eigen/Dense>
namespace util{

typedef struct trPar{
    std::string cmd;
    Eigen::Vector3d vec;
    double num;
} trPar;

}
#endif // UTIL_H
