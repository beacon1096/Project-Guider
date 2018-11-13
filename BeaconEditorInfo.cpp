#include "BeaconEditorInfo.h"

/*BeaconEditorInfo::BeaconEditorInfo(QObject *parent) : QObject(parent)
{

}*/
BeaconEditorInfo::BeaconEditorInfo(QString filePathArg)//,QObject *parent=nullptr) : QObject(parent)
{
    filePath=filePathArg;
    _genFileName();
    _genSuffix();
    _genExecutablePath();
    changed=false;
}
BeaconEditorInfo::BeaconEditorInfo(const BeaconEditorInfo &source){
    this->filePath=source.filePath;
    _genFileName();
    _genSuffix();
    _genExecutablePath();
    changed=false;
}
bool BeaconEditorInfo::updateChangedStatus(bool state){
    changed=state;
    return true;
}
void BeaconEditorInfo::operator=(const BeaconEditorInfo &source){
    this->filePath=source.filePath;
    _genFileName();
    _genSuffix();
    _genExecutablePath();
    changed=false;
}
void BeaconEditorInfo::setProperty(BeaconEditorInfo &source){
    this->filePath=source.filePath;
    _genFileName();
    _genSuffix();
    _genExecutablePath();
    changed=false;
}
void BeaconEditorInfo::setProperty(QString &source){
    this->filePath=source;
    qDebug() << "FilePath -> " << source;
    _genFileName();
    _genSuffix();
    _genExecutablePath();
    changed=false;
}
void BeaconEditorInfo::_genFileName(){
    fileName=filePath.split('/').last();
    qDebug() << "FileName -> " << fileName;
}
void BeaconEditorInfo::_genSuffix(){
    suffix=filePath.split('.').last();
    qDebug() << "suffix -> "<< suffix;
}
void BeaconEditorInfo::_genExecutablePath(){
    QStringList t=filePath.split('.');
    t.removeLast();
    if(BeaconPlatformInfo::isWindows)t.append("exe");
    executablePath = t.join('.');
    qDebug() << "executable -> " << executablePath;
}
void BeaconEditorInfo::updateInfo(){
    _genFileName();
    _genSuffix();
    _genExecutablePath();
}
