#include "basereader.h"

basereader::basereader()
{}
basereader::~basereader()
{
    _filePath.clear();
    _file.close();

}
basereader::basereader(const string& filePath, std::ios_base::openmode mode)
{
    _filePath=filePath;
    _mode=mode;
}
int basereader::openFile()
{
    int retVal=1;
    try {
        _file.open(_filePath, _mode);
    } catch (int) {
        retVal=0;
    }

    return retVal;
}
int basereader::openFile(const string& filePath, std::ios_base::openmode mode)
{
    int retVal=1;
    try {
        _file.open(filePath, mode);
    } catch (int) {
        retVal=0;
    }

    return retVal;
}
int basereader::closeFile()
{
    _filePath.clear();
    _file.close();
    return 1;
}
void basereader::setPath(const string& filePath)
{
    _filePath=filePath;
}
void basereader::setMode(std::ios_base::openmode mode)
{
    _mode=mode;
}
bool basereader::isReady()
{
    return _file.is_open()?true:false;
}
ifstream& basereader::iFStream()
{
    return _file;
}
