#ifndef READ_OBJ_H
#define READ_OBJ_H
#include<basereader.h>


class read_obj:basereader
{
public:
    read_obj();
    read_obj(const string fileStr);
    int getGeom(vector<Eigen::Vector3d>& vertE,vector<array<int, 3>>& facE);
};

#endif // READ_OBJ_H
