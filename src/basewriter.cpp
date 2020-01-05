#include "basewriter.h"

baseWriter::baseWriter(){
    _mode=ios::binary;
}
baseWriter::~baseWriter(){
    _filePath.clear();
    closeFile();
}
baseWriter::baseWriter(const string& filePath, ios_base::openmode mode)
{
    _mode=mode;
    _filePath=filePath;

}
void baseWriter::setMode(ios_base::openmode mode)
{
    _mode=mode;

}
void baseWriter::setPath(const string& filePath)
{
    _filePath=filePath;
}

ofstream& baseWriter::oFStream()
{
    return _file;
}

bool baseWriter::isReady()
{
    bool retVal=false;
    if (_file.is_open())
    {
        retVal= true;
    }
    return retVal;
}
int baseWriter::openFile(const string& filePath, ios_base::openmode mode)
{
    int retVal=1;
    try{
        _file.open(filePath, mode);
    }catch(const std::exception&){
        retVal= 0;
    }
    return retVal;
}
int baseWriter::openFile()
{
    int retVal=1;
    if(!_filePath.empty()){
        try{
            _file.open(_filePath, _mode);
        }catch(const std::exception&){
            retVal= 0;
        }
        return 1;
    }else{
        retVal=0;
    }
    return retVal;
}
int baseWriter::closeFile()
{
    int retVal=1;
    try {
        _file.close();
    } catch (const std::exception&) {
        retVal=0;
    }
    return retVal;
}
