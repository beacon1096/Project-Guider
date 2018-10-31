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
    _genFileName();
    _genSuffix();
    _genExecutablePath();
    changed=false;
}
void BeaconEditorInfo::_genFileName(){
    fileName=filePath.split('/').last();;
}
void BeaconEditorInfo::_genSuffix(){
    suffix=filePath.split('.').last();
}
void BeaconEditorInfo::_genExecutablePath(){
    if(BeaconPlatformInfo::isWindows){
        executablePath=filePath.replace(suffix,"exe");
    }
    else{
        QStringList t=filePath.split('.');
        t.removeLast();
        executablePath = t.join('.');
    }
}
