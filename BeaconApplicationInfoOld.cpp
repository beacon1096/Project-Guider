#include "BeaconApplicationInfoOld.h"

BeaconApplicationInfo::BeaconApplicationInfo(QObject *parent) : QObject(parent)
{
    setComponentName(MainInfo::componentName);
    setDisplayName(MainInfo::displayName);
    setVersion(MainInfo::version);
    setShortDescription(MainInfo::shortDescription);
    setCopyrightStatement(MainInfo::copyrightStatement);
    setHomepage(MainInfo::homepage);
    setLicense(MainInfo::license);
    setBugAddress(MainInfo::bugAddress);
    setOcsProvider(MainInfo::ocsProvider);
    setProgramLogo(MainInfo::programLogo);
    setOtherText(MainInfo::otherText);
    setBuildType(MainInfo::buildType);
}

void BeaconApplicationInfo::setBugAddress(QString target){
    bugAddress=target;
}
void BeaconApplicationInfo::setComponentName(QString target){
    componentName=target;
}
void BeaconApplicationInfo::setCopyrightStatement(QString target){
    copyrightStatement=target;
}
void BeaconApplicationInfo::setHomepage(QString target){
    homepage=target;
}
void BeaconApplicationInfo::setOcsProvider(QString target){
    ocsProvider=target;
}
void BeaconApplicationInfo::setOtherText(QString target){
    otherText=target;
}
void BeaconApplicationInfo::setProgramLogo(QString target){
    programLogo=target;
}
void BeaconApplicationInfo::setShortDescription(QString target){
    shortDescription=target;
}
void BeaconApplicationInfo::setVersion(QString target){
    version=target;
}
void BeaconApplicationInfo::setDisplayName(QString target){
    displayName=target;
}
void BeaconApplicationInfo::setLicense(QString target){
    license=target;
}
void BeaconApplicationInfo::setBuildType(QString target){
    buildType=target;
}
