#include <QCoreApplication>
#include <QStandardPaths>
#include "BeaconApplicationInfo.h"
#include "BeaconFileIO.h"

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
    p=other.p;
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
BeaconAboutLicense &BeaconAboutLicense::operator=(const BeaconAboutLicense &other){
    p=other.p;
    return *this;
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
    case BeaconAboutLicense::GPL_V2:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","GPL v2", "license item");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","GNU General Public License Version 2","license item");
        break;
    case BeaconAboutLicense::GPL_V3:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","GPL v3","license item");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","GNU General Public License Version 3","license item");
        break;
    case BeaconAboutLicense::LGPL_V2:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","LGPL v2","license item");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","GNU Lesser General Public License Version 2","license item");
        break;
    case BeaconAboutLicense::LGPL_V2_1:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","LGPL v2.1","license item");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","GNU Lesser General Public License Version 2.1","license item");
        break;
    case BeaconAboutLicense::LGPL_V3:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","LGPL v3","license item");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","GNU Lesser General Public License Version 3","license item");
        break;
    case BeaconAboutLicense::QPL_V1_0:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","QPL v1.0","license item");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","Q Public License","license item");
        break;
    case BeaconAboutLicense::Unknown:
        licenseShort = QCoreApplication::translate("BeaconAboutLicense","Unknown","license item:short");
        licenseFull = QCoreApplication::translate("BeaconAboutLicense","Unknown","license item:full");
        break;
    default:
        licenseShort = licenseFull = QCoreApplication::translate("BeaconAboutLicense","Not sprcified","license item");
        break;
    }
    const QString result =
            (formatName == BeaconAboutLicense::ShortName) ? licenseShort:
            (formatName == BeaconAboutLicense::FullName) ? licenseFull:
            QString();
    return result;
}
BeaconAboutLicense::LicenseKey BeaconAboutLicense::key(){
    return this->p->_licenseKey;
}
void BeaconAboutLicense::setLicenseFromFile(const QString &pathToFile){
    p->_licenseKey = BeaconAboutLicense::File;
    p->_pathToLicenseTextFile = pathToFile;
}
void BeaconAboutLicense::setLicenseFromText(const QString &text){
    p->_licenseKey = BeaconAboutLicense::Custom;
    p->_licenseText = text;
}
QString BeaconAboutLicense::text(){
    QString result;

    const QString lineFeed = QStringLiteral("\n\n");
    QString pathToFile;

    if(p->_aboutInfo && !p->_aboutInfo->copyRightStatement().isEmpty()) {
        result = p->_aboutInfo->copyRightStatement() + lineFeed;
    }
    bool knownLicense=false;
    switch (p->_licenseKey) {
    case BeaconAboutLicense::File:
        pathToFile = p->_pathToLicenseTextFile;
        break;
    case BeaconAboutLicense::BSDL:
        pathToFile = QStringLiteral("BSD");
        knownLicense=true;
        break;
    case BeaconAboutLicense::GPL_V2:
        pathToFile = QStringLiteral("GPL_V2");
        knownLicense=true;
        break;
    case BeaconAboutLicense::GPL_V3:
        pathToFile = QStringLiteral("GPL_V3");
        knownLicense=true;
        break;
    case BeaconAboutLicense::LGPL_V2:
        pathToFile = QStringLiteral("LGPL_V2");
        knownLicense=true;
        break;
    case BeaconAboutLicense::LGPL_V2_1:
        pathToFile = QStringLiteral("LGPL_V21");
        knownLicense=true;
        break;
    case BeaconAboutLicense::LGPL_V3:
        pathToFile = QStringLiteral("LGPL_V3");
        knownLicense=true;
        break;
    case BeaconAboutLicense::QPL_V1_0:
        pathToFile = QStringLiteral("QPL_V10");
        knownLicense=true;
        break;
    case BeaconAboutLicense::Artistic:
        pathToFile = QStringLiteral("ARTISTIC");
        knownLicense=true;
        break;
    case BeaconAboutLicense::Custom:
        if(!p->_licenseText.isEmpty()){
            result = p->_licenseText;
            break;
        }
    default:
        result += QCoreApplication::translate("BeaconAboutLicense",
                                              "No licensing term for this program have been specified."
                                              "\n"
                                              "Please check the documentation or the source for any licensing terms."
                                              "\n"
                                              );
    }
    if(knownLicense){
        pathToFile = QString::fromLocal8Bit(":/BF/licenses/")+pathToFile;
        result += QCoreApplication::translate("BeaconAboutLicense",
                                              "This program is distributed under the terms of the %1.").arg(name(BeaconAboutLicense::ShortName));
        if(!pathToFile.isEmpty()){
            result += lineFeed;
        }
    }
    if(!pathToFile.isEmpty()){
        result += BeaconFileIO::readFileContent(pathToFile);
    }
    return result;
}
