#include "read_obj.h"

read_obj::read_obj()
{

}
read_obj::read_obj(const string fileStr):basereader(fileStr, std::ios::in){}
int read_obj::getGeom(vector<Eigen::Vector3d>& vertEV,vector<array<int, 3>>& facV)
{
    int retVal=0;
    string lineFF;
    if(!this->isReady()){
        this->openFile();
    }
    if(this->isReady()){
        std::vector<std::string> lineVec;
        vector<int> buf;
        while(getline(this->iFStream(),lineFF)){
            lineVec.clear();
            lineVec=strSplit(lineFF, " ");
            if (lineVec.size()){
                switch (lineVec[0][0]) {
                case 'v':
                    if(lineVec[0].size()==1){
                        vertEV.push_back(Eigen::Vector3d(stod(lineVec[1]),stod(lineVec[2]),stod(lineVec[3])));
                    }
                    break;
                case 'f':
                    if(lineVec[0].size()==1){
                        buf.clear();
                        for(size_t iii=0; iii<lineVec.size()-1;iii++){
                            buf.push_back(stoi(strSplit(lineVec[iii+1], "/")[0]));

                        }
                        if(buf.size()>3){
                            for(size_t iii=0; iii<buf.size()-2;iii++){
                                facV.push_back(array<int,3>{buf[0], buf[iii+1], buf[iii+2]});
                            }
                        }else{
                            //cout<< "BUF 1: "<< buf[0]<< " 2: "<< buf[1]<<" 3: " << buf[2]<<endl;
                            facV.push_back(array<int,3>{buf[0], buf[1], buf[2]});
                        }
                    }

                    break;
                default:
                    break;

                }
            }
        }
        retVal=1;
    }
    return retVal;

}
