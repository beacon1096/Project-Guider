#include "BeaconCodeProperty.h"

/*BeaconCodeProperty::BeaconCodeProperty(QObject *parent) : QObject(parent)
{

}*/
BeaconCodeProperty::BeaconCodeProperty(QString filePathArg)//,QObject *parent=nullptr) : QObject(parent)
{
    filePath=filePathArg;
    fileName=filePathArg.split('/').last();
    changed=false;
}
BeaconCodeProperty::BeaconCodeProperty(const BeaconCodeProperty &source){
    this->filePath=source.filePath;
    fileName=filePath.split('/').last();
    changed=false;
}
bool BeaconCodeProperty::updateChangedStatus(bool state){
    changed=state;
    return true;
}
void BeaconCodeProperty::operator=(const BeaconCodeProperty &source){
    this->filePath=source.filePath;
    fileName=filePath.split('/').last();
    changed=false;
}
void BeaconCodeProperty::setProperty(BeaconCodeProperty &source){
    this->filePath=source.filePath;
    fileName=filePath.split('/').last();
    changed=false;
}
void BeaconCodeProperty::setProperty(QString &source){
    this->filePath=source;
    fileName=filePath.split('/').last();
    changed=false;
}
