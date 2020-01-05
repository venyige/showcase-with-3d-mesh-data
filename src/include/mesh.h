#ifndef MESH_H
#define MESH_H
#include<iostream>
#include<array>
#include<memory>
#include<Eigen/Geometry>
#include<vector>
#include<util.h>
using namespace std;
using namespace Eigen;


class mesh
{
public:
    mesh();
    mesh(vector<Vector3d> v, vector<Vector3d> vt, vector<Vector3d> vn,vector<array<size_t, 3>> f);
    ~mesh();
    vector<Eigen::Vector3d>& v(){return _v;}
    vector<Eigen::Vector3d>& n(){return _vn;}
    vector<array<size_t, 3>>& f(){return _f;}
    void setTransform(Eigen::Affine3d );
    void resetTrans();
    void addTranslation(Eigen::Vector3d );
    void addTranslation(double, double, double);
    void addRotation(double, Vector3d);
    void addScaling(Vector3d);
    void performTransforms();
    void generateNormals();
    bool checkInclusion(Eigen::Vector3d&);
private:
    vector<Eigen::Vector3d> _v;
    vector<Eigen::Vector3d> _vt; /* for later use */
    vector<Eigen::Vector3d> _vn; /* for later use */
    vector<array<size_t, 3>> _f;
    Eigen::Affine3d _t;
    Vector3d _p;
};

#endif // MESH_H
