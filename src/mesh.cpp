#include "mesh.h"

mesh::mesh()
{
    _t.setIdentity();
}
mesh::mesh(vector<Vector3d> v, vector<Vector3d>, vector<Vector3d> vn,vector<array<size_t, 3>> f )
{
    _t.setIdentity();
    _v=v;
    //   _vt=vt; //future feature
    _vn=vn;
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



#define triPt(a) this->_v[triI[a]-1]
#define triPtA triPt(0)
#define triPtB triPt(1)
#define triPtC triPt(2)
bool mesh::checkInclusion(Eigen::Vector3d& poI)
{
    double zRef=poI.z();
    size_t norii=0;
    double zHit;
    size_t hitCounter=0;
    for(auto triI: this->_f){
        //      Exclude groupA
        if((triPtA.z()<zRef)&&(triPtB.z()<zRef)&&(triPtB.z()<zRef)){
            norii++;
            continue;
        }
        if(util::ptInTriangle(poI, triPtA, triPtB, triPtC)){
            //   Now the plane-halfray eqation system is needed
            //      a(x−x0)+b(y−y0)+c(z−z0)=0
            if((triPtA.z()>zRef)&&(triPtB.z()>zRef)&&(triPtB.z()>zRef)){
                hitCounter++;
            }else{
                zHit=triPtA.z()+(this->_vn[norii].x()*(triPtA.x()-poI.x())-this->_vn[norii].y()*(triPtA.y()-poI.y()))/this->_vn[norii].z();
                if(zHit>=zRef)
                    hitCounter++;
            }
        }
        norii++;
    }
    //Oddity check
    return hitCounter&1;
}

void mesh::generateNormals()
{
    this->_vn.clear();
    for(auto triI: this->_f){
        this->_vn.push_back(((triPtB-triPtA).cross(triPtC-triPtA)).normalized());
    }
}
/*
#define triPt(a) this->_v[fc[a]-1]
#define triPtA triPt(0)
#define triPtB triPt(1)
#define triPtC triPt(2)
void mesh::generateNormals()
{
    unique_ptr<size_t> vP=make_unique<size_t>(size_t(0));
    std::transform(_f.begin(), _f.end(), _vn.begin(), [&](array<size_t, 3>& fc){
        std::cout<<triPtA<<endl;
        return ((triPtB-triPtA).cross(triPtC-triPtA)).normalized();});

}
*/
