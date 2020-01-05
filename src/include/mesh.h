#ifndef MESH_H
#define MESH_H
#include<array>
#include<memory>
#include<Eigen/Geometry>
#include<vector>
using namespace std;
using namespace Eigen;


class mesh
{
public:
    mesh();
    mesh(vector<Vector3d> v, vector<Vector3d> vt, vector<Vector3d> vn,vector<array<int, 3>> f);
    ~mesh();
    vector<Eigen::Vector3d>& v(){return _v;}
    vector<array<int, 3>>& f(){return _f;}
    void setTransform(Eigen::Affine3d );
    void resetTrans();
    void addTranslation(Eigen::Vector3d );
    void     addTranslation(double, double, double);
    void addRotation(double, Vector3d);
    void addScaling(Vector3d);
    void performTransforms();
private:
    vector<Eigen::Vector3d> _v;
    vector<Eigen::Vector3d> _vt; /* for later use */
    vector<Eigen::Vector3d> _vn; /* for later use */
    vector<array<int, 3>> _f;
    Eigen::Affine3d _t;
    Vector3d _p;
};

#endif // MESH_H
