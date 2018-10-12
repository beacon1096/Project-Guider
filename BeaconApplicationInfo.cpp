#include <QCoreApplication>
#include "BeaconApplicationInfo.h"

class BeaconAboutPerson::personPrivate{
public:
    QString _name;
    QString _task;
    QString _emailAddress;
    QString _homePage;
    QString _oscUsername;
};

BeaconAboutPerson::BeaconAboutPerson(const QString name,
                                     const QString task,
                                     const QString emailAddress,
                                     const QString homePage,
                                     const QString oscUsername) : QObject()
{
    this->p->_name=name;
    this->p->_task=task;
    this->p->_emailAddress=emailAddress;
    this->p->_homePage=homePage;
    this->p->_oscUsername=oscUsername;
}
BeaconAboutPerson::BeaconAboutPerson(const BeaconAboutPerson &other){
    this->p=other.p;
}
BeaconAboutPerson::~BeaconAboutPerson(){
    delete p;
}
BeaconAboutPerson &BeaconAboutPerson::operator=(const BeaconAboutPerson &other){
    *p=*other.p;
    return *this;
}
QString BeaconAboutPerson::name(){
    return this->p->_name;
}
QString BeaconAboutPerson::task(){
    return this->p->_task;
}
QString BeaconAboutPerson::emailAddress(){
    return this->p->_emailAddress;
}
QString BeaconAboutPerson::homePage(){
    return this->p->_homePage;
}
QString BeaconAboutPerson::oscUsername(){
    return this->p->_oscUsername;
}

class BeaconAboutLicense::licensePrivate : public QSharedData{
public:
    licensePrivate(LicenseKey licenseType,
                   VersionRestriction versionRestriction,
                   const BeaconApplicationInfo *aboutData);
    licensePrivate(const licensePrivate &other);

    LicenseKey _licenseKey;
    QString _licenseText;
    QString _pathToLicenseTextFile;
    VersionRestriction _versionRestriction;
    const BeaconApplicationInfo *_aboutInfo;
};
BeaconAboutLicense::licensePrivate::licensePrivate(LicenseKey licenseType,
                                                   VersionRestriction versionRestriction,
                                                   const BeaconApplicationInfo *aboutInfo)
    :QSharedData (),
      _licenseKey(licenseType),
      _versionRestriction(versionRestriction),
      _aboutInfo(aboutInfo)
{
}

BeaconAboutLicense::licensePrivate::licensePrivate(const licensePrivate &other)
    :QSharedData (other),
      _licenseKey(other._licenseKey),
      _versionRestriction(other._versionRestriction),
      _aboutInfo(other._aboutInfo)
{
}
BeaconAboutLicense::BeaconAboutLicense(LicenseKey licenseType,
                                       VersionRestriction versionRestriction,
                                       const BeaconApplicationInfo *aboutInfo)
    :p(new licensePrivate(licenseType,versionRestriction,aboutInfo))
{
}
BeaconAboutLicense::BeaconAboutLicense(LicenseKey licenseType,
                                       const BeaconApplicationInfo *aboutInfo)
    :p(new licensePrivate(licenseType,OnlyThisVersion,aboutInfo))
{
}
BeaconAboutLicense::BeaconAboutLicense(const BeaconApplicationInfo *aboutInfo)
    :p(new licensePrivate(Unknown,OnlyThisVersion,aboutInfo))
{
}
BeaconAboutLicense::BeaconAboutLicense(const BeaconAboutLicense &other)
    :p(other.p)
{
}
BeaconAboutLicense::~BeaconAboutLicense()
{}
QString BeaconAboutLicense::name(NameFormat formatName){
    QString licenseShort;
    QString licenseFull;
    switch (p->_licenseKey) {
    case BeaconAboutLicense::Artistic:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","Artistic License","license item:short");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","Artistic License","license item:full");
        break;
    case BeaconAboutLicense::BSDL:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","BSD License","license item:short");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","BSD License","license item:full");
        break;
    case BeaconAboutLicense::Custom:
    case BeaconAboutLicense::File:
        licenseShort = licenseFull = QCoreApplication::translate("BeaconAboutLicense","Custom","license item");
        break;

}
