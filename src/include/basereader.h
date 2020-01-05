#ifndef BASEREADER_H
#define BASEREADER_H
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<array>
#include<Eigen/Dense>
using namespace std;

class basereader
{
public:
    basereader();
    basereader(const string& filePath, ios_base::openmode mode=ios::binary|ios::in);
    virtual ~basereader();
    /* ===================
Utility functions
======================*/
    static bool chkFile(string name){
        bool retVal=false;
        ifstream f(name.c_str());
        retVal= f.good();
        return retVal;
    }
    static vector<string> strSplit(const string &string, const std::string &delim) {
        vector<std::string> retVec;
        string::size_type lastPos = string.find_first_not_of(delim, 0);
        string::size_type actPos = string.find_first_of(delim, lastPos);

        while (string::npos != actPos || string::npos != lastPos) {
            retVec.push_back(string.substr(lastPos, actPos - lastPos));
            lastPos = string.find_first_not_of(delim, actPos);
            actPos = string.find_first_of(delim, lastPos);
        }

        return retVec;
    }
protected:
    int openFile();
    int openFile(const string& filePath, ios_base::openmode mode=ios::binary|ios::in);
    int closeFile();
    void setPath(const string& filePath);
    void setMode(ios_base::openmode mode);
    bool isReady();
    ifstream& iFStream();
private:
    string _filePath;
    ifstream _file;
    ios_base::openmode _mode;
};


#endif // BASEREADER_H
