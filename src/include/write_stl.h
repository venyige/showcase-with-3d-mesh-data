#ifndef WRITE_STL_H
#define WRITE_STL_H
#include<basewriter.h>
#include<memory>
#include<array>
#include<vector>
#include<Eigen/Dense>


class write_stl:baseWriter
{
public:
    write_stl();
    write_stl(const string& fileStr,
              std::shared_ptr<vector<Eigen::Vector3d>> ptArray,
              std::shared_ptr<vector<array<int, 3>>> ptFace);
    ~write_stl();

    void dumpFile();

private:
    std::shared_ptr<vector<Eigen::Vector3d>> _ptV;
    std::shared_ptr<vector<array<int, 3>>> _ptF;
};

#endif // WRITE_STL_H
