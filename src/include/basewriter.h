#ifndef BASEWRITER_H
#define BASEWRITER_H
#include<string>
#include<fstream>
using namespace std;

class baseWriter
{
public:
    baseWriter();
    baseWriter(const string& filePath, std::ios_base::openmode mode=ios::binary|ios::out);
    virtual ~baseWriter();

protected:
    int openFile();
    int openFile(const string& filePath, std::ios_base::openmode mode=ios::binary|ios::out);
    int closeFile();
    void setPath(const string& filePath);
    void setMode(std::ios_base::openmode mode);
    bool isReady();
    ofstream& oFStream();
private:
    string _filePath;
    ofstream _file;
    ios_base::openmode _mode;
};

#endif // BASEWRITER_H
