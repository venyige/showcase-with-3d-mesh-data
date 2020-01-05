#include "write_stl.h"

write_stl::write_stl()
{}

write_stl::write_stl(const string& fileStr, std::shared_ptr<vector<Eigen::Vector3d>> ptArray,
                     std::shared_ptr<vector<Eigen::Vector3d>> ptNorm,
                     std::shared_ptr<vector<array<size_t, 3>>> ptFace):baseWriter (fileStr)
{
    _ptV=ptArray;
    _ptN=ptNorm;
    _ptF=ptFace;
    setPath(fileStr);
}
write_stl::~write_stl()
{
    closeFile();
}
void write_stl::dumpFile()
{
    char head[80] = { 0 };
    uint32_t numFaces=this->_ptF->size();
    uint16_t zero2=0;
    float cTnr=0.0;
    size_t vii;
    string headStr("Created by \"tcmu\" 3D file conversion utility\nGoDraw");
    //for_each(headStr.begin(), headStr.end(), [])
    std::transform(headStr.begin(), headStr.end(), head,
                   [](unsigned char c){ return static_cast<uint8_t>(c); });

    if(!this->isReady())
        this->openFile();
    if(this->isReady()){
        this->oFStream().write(head, 80);
        this->oFStream().write(reinterpret_cast<char*>(&numFaces), 4);
        for(size_t iii=0; iii<numFaces; iii++){
            cTnr=float((*_ptN)[iii][0]);
            this->oFStream().write(reinterpret_cast<char*>(&cTnr), 4);
            cTnr=float((*_ptN)[iii][1]);
            this->oFStream().write(reinterpret_cast<char*>(&cTnr), 4);
            cTnr=float((*_ptN)[iii][2]);
            this->oFStream().write(reinterpret_cast<char*>(&cTnr), 4);
            for(size_t jjj=0; jjj<3; jjj++){
                vii=size_t((*_ptF)[iii][jjj]-1);
                cTnr=float((*_ptV)[vii][0]);
                this->oFStream().write(reinterpret_cast<char*>(&cTnr), 4);
                cTnr=float((*_ptV)[vii][1]);
                this->oFStream().write(reinterpret_cast<char*>(&cTnr), 4);
                cTnr=float((*_ptV)[vii][2]);
                this->oFStream().write(reinterpret_cast<char*>(&cTnr), 4);
            }
            this->oFStream().write(reinterpret_cast<char*>(&zero2), 2);
        }


    }
}

