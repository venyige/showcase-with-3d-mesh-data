#include "mesh.h"

mesh::mesh()
{
    _t.setIdentity();
}
mesh::mesh(vector<Vector3d> v, vector<Vector3d> , vector<Vector3d> ,vector<array<int, 3>> f )
{
    _t.setIdentity();
    _v=v;
    //   _vt=vt; //future feature
    //   _vn=vn; //future feature
    _f=f;
}

mesh::~mesh()
{}
void mesh::resetTrans()
{
    _t.setIdentity();
}
void mesh::setTransform(Eigen::Affine3d t)
{
    _t=t;
}
void mesh::addTranslation(Eigen::Vector3d t)
{
    Eigen::Translation3d tT(t);
    _t=_t*tT;
}
void mesh::addTranslation(double x, double y, double z)
{
    Eigen::Vector3d t(x,y,z);
    Eigen::Translation3d tT(t);
    _t=_t*tT;
}
void mesh::addRotation(double angle, Vector3d ax)
{
    Eigen::AngleAxisd rot(angle*M_PI/180.0, ax.normalized());
    _t=_t*rot;
}
void mesh::addScaling(Vector3d scale)
{
    DiagonalMatrix<double, 3> sd(scale);
    _t=_t*sd;
}
void mesh::performTransforms()
{
    if(!_t.matrix().isIdentity()){
        for_each(_v.begin(), _v.end(), [=](Vector3d& pt){
            pt=this->_t*pt;
        });
    }

}
void mesh::generateNormals()
{
    unique_ptr<size_t> vP=make_unique<size_t>(size_t(0));
    std::transform(_f.begin(), _f.end(), _vn.begin(), [=](array<int, 3>& /*fc*/){
 //       this->_v[fc[0]];
        return Eigen::Vector3d(0,0,0);});
}
