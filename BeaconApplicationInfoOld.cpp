#include "BeaconApplicationInfoOld.h"

BeaconApplicationInfoOld::BeaconApplicationInfoOld(QObject *parent) : QObject(parent)
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

void BeaconApplicationInfoOld::setBugAddress(QString target){
    bugAddress=target;
}
void BeaconApplicationInfoOld::setComponentName(QString target){
    componentName=target;
}
void BeaconApplicationInfoOld::setCopyrightStatement(QString target){
    copyrightStatement=target;
}
void BeaconApplicationInfoOld::setHomepage(QString target){
    homepage=target;
}
void BeaconApplicationInfoOld::setOcsProvider(QString target){
    ocsProvider=target;
}
void BeaconApplicationInfoOld::setOtherText(QString target){
    otherText=target;
}
void BeaconApplicationInfoOld::setProgramLogo(QString target){
    programLogo=target;
}
void BeaconApplicationInfoOld::setShortDescription(QString target){
    shortDescription=target;
}
void BeaconApplicationInfoOld::setVersion(QString target){
    version=target;
}
void BeaconApplicationInfoOld::setDisplayName(QString target){
    displayName=target;
}
void BeaconApplicationInfoOld::setLicense(QString target){
    license=target;
}
void BeaconApplicationInfoOld::setBuildType(QString target){
    buildType=target;
}
