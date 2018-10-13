#include <QCoreApplication>
#include <QStandardPaths>
#include <QGlobalStatic>
#include <QUrl>
#include "BeaconApplicationInfo.h"
#include "BeaconFileIO.h"

class BeaconAboutPerson::personPrivate{
public:
    QString _name;
    QString _task;
    QString _emailAddress;
    QString _homePage;
    QString _ocsUsername;
};

BeaconAboutPerson::BeaconAboutPerson(const QString name,
                                     const QString task,
                                     const QString emailAddress,
                                     const QString homePage,
                                     const QString ocsUsername) : QObject()
{
    this->p->_name=name;
    this->p->_task=task;
    this->p->_emailAddress=emailAddress;
    this->p->_homePage=homePage;
    this->p->_ocsUsername=ocsUsername;
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
QString BeaconAboutPerson::ocsUsername(){
    return this->p->_ocsUsername;
}

class BeaconAboutLicense::licensePrivate : public QSharedData{
public:
    licensePrivate(LicenseKey licenseType,
                   VersionRestriction versionRestriction,
                   BeaconApplicationInfo *aboutData);
    licensePrivate(const licensePrivate &other);

    LicenseKey _licenseKey;
    QString _licenseText;
    QString _pathToLicenseTextFile;
    VersionRestriction _versionRestriction;
    BeaconApplicationInfo *_aboutInfo;
};
BeaconAboutLicense::licensePrivate::licensePrivate(LicenseKey licenseType,
                                                   VersionRestriction versionRestriction,
                                                   BeaconApplicationInfo *aboutInfo)
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
                                       BeaconApplicationInfo *aboutInfo)
    :p(new licensePrivate(licenseType,versionRestriction,aboutInfo))
{
}
BeaconAboutLicense::BeaconAboutLicense(LicenseKey licenseType,
                                       BeaconApplicationInfo *aboutInfo)
    :p(new licensePrivate(licenseType,OnlyThisVersion,aboutInfo))
{
}
BeaconAboutLicense::BeaconAboutLicense(BeaconApplicationInfo *aboutInfo)
    :p(new licensePrivate(Unknown,OnlyThisVersion,aboutInfo))
{
}
BeaconAboutLicense::BeaconAboutLicense(BeaconAboutLicense &other)
    :p(other.p)
{
}
BeaconAboutLicense &BeaconAboutLicense::operator=(BeaconAboutLicense &other){
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

    if(p->_aboutInfo && !p->_aboutInfo->copyrightStatement().isEmpty()) {
        result = p->_aboutInfo->copyrightStatement() + lineFeed;
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
class BeaconApplicationInfo::InfoPrivate{
public:
    InfoPrivate()
        : customAuthorTextEnabled(false)
    {}
    QString _componentName;
    QString _displayName;
    QString _shortDescription;
    QString _copyrightStatement;
    QString _otherText;
    QString _homepageAddress;
    QList<BeaconAboutPerson> _authorList;
    QList<BeaconAboutPerson> _creditList;
    QList<BeaconAboutPerson> _translatorList;
    QList<BeaconAboutLicense> _licenseList;
    QString productName;
    QString programIconName;
    QVariant programLogo;
    QString customAuthorPlainText, customAuthorRichText;
    bool customAuthorTextEnabled;

    QString organizationDomain;
    QString _ocsProviderUrl;
    QString desktopFileName;

    static QList<BeaconAboutPerson> parseTranslators(const QString &translatorName, const QString &translatorEmail);

    QByteArray _internalProgramName;
    QByteArray _version;
    QByteArray _bugAddress;
};
BeaconApplicationInfo::BeaconApplicationInfo(const QString &componentName,
                                             const QString &displayName,
                                             const QString &version,
                                             const QString &shortDescription,
                                             enum BeaconAboutLicense::LicenseKey licenseType,
                                             const QString &copyrightStatement,
                                             const QString &text,
                                             const QString &homePageAddress,
                                             const QString &bugAddress
                                             )
    : p(new InfoPrivate)
{
    p->_componentName = componentName;
    int sp = p->_componentName.indexOf(QLatin1Char('/'));
    if(sp >= 0){
        p->_componentName = p->_componentName.mid(sp+1);
    }

    p->_displayName = displayName;
    if(!p->_displayName.isEmpty()){
        p->_internalProgramName = displayName.toUtf8();
    }

    p->_version = version.toUtf8();
    p->_shortDescription = shortDescription;
    p->_licenseList.append(BeaconAboutLicense(licenseType, this));
    p->_copyrightStatement = copyrightStatement;
    p->_otherText = text;
    p->_homepageAddress = homePageAddress;
    p->_bugAddress = bugAddress.toUtf8();

    QUrl homePageUrl(homePageAddress);
    if (!homePageUrl.isValid() || homePageUrl.scheme().isEmpty()) {
        homePageUrl.setUrl(QStringLiteral("https://beacon1096.github.io/"));
    }

    const QChar dotChar(QLatin1Char('.'));
    QStringList hostComponents = homePageUrl.host().split(dotChar);

    if (hostComponents.size() > 2) {
        hostComponents.removeFirst();
    }

    p->organizationDomain = hostComponents.join(dotChar);

    std::reverse(hostComponents.begin(), hostComponents.end());
    hostComponents.append(componentName);

    p->desktopFileName = hostComponents.join(dotChar);
}

BeaconApplicationInfo::BeaconApplicationInfo(const QString &componentName,
                                             const QString &displayName,
                                             const QString &version
                                            )
    : p(new InfoPrivate)
{
    p->_componentName = componentName;
    int sp = p->_componentName.indexOf(QLatin1Char('/'));
    if(sp >= 0){
        p->_componentName = p->_componentName.mid(sp+1);
    }

    p->_displayName = displayName;
    if(!p->_displayName.isEmpty()){
        p->_internalProgramName = displayName.toUtf8();
    }

    p->_version = version.toUtf8();

    p->_licenseList.append(BeaconAboutLicense(BeaconAboutLicense::Unknown, this));
    p->_bugAddress = "Beacon1096@outlook.com";
    p->organizationDomain = QStringLiteral("Beacon1096.io");
    p->desktopFileName = QStringLiteral("io.Beacon1096.%1").arg(p->_componentName);
}

BeaconApplicationInfo::~BeaconApplicationInfo(){
    delete p;
}

BeaconApplicationInfo::BeaconApplicationInfo(const BeaconApplicationInfo &other): p(new InfoPrivate){
    *p = *other.p;
    QList<BeaconAboutLicense>::iterator it = p->_licenseList.begin();
    QList<BeaconAboutLicense>::iterator itEnd = p->_licenseList.end();
    for (; it != itEnd; ++it) {
        BeaconAboutLicense &al = *it;
        al.p.detach();
        al.p->_aboutInfo = this;
    }
}

BeaconApplicationInfo &BeaconApplicationInfo::addAuthor(const QString &name,
                                                        const QString &task,
                                                        const QString &emailAddress,
                                                        const QString &homePage,
                                                        const QString &ocsUsername
                                                        )
{
    p->_authorList.append(BeaconAboutPerson(name,task,emailAddress,homePage,ocsUsername));
}

BeaconApplicationInfo &BeaconApplicationInfo::addCredit(const QString &name,
                                                        const QString &task,
                                                        const QString &emailAddress,
                                                        const QString &homePage,
                                                        const QString &ocsUsername
                                                        )
{
    p->_creditList.append(BeaconAboutPerson(name,task,emailAddress,homePage,ocsUsername));
}

BeaconApplicationInfo &BeaconApplicationInfo::addTranslator(const QString &name,
                                                            const QString &emailAddress
                                                            )
{
    p->_translatorList = InfoPrivate::parseTranslators(name,emailAddress);
}

BeaconApplicationInfo &BeaconApplicationInfo::setLicenseText(const QString &license)
{
    p->_licenseList[0] = BeaconAboutLicense(this);
    p->_licenseList[0].setLicenseFromText(license);
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::addLicenseText(const QString &license)
{
    BeaconAboutLicense &firstLicense = p->_licenseList[0];
    BeaconAboutLicense newLicense(this);
    newLicense.setLicenseFromText(license);
    if(p->_licenseList.count() ==1 && firstLicense.p->_licenseKey == BeaconAboutLicense::Unknown){
        firstLicense = newLicense;
    }else{
        p->_licenseList.append(newLicense);
    }
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setLicenseTextFile(const QString &pathToFile)
{
    p->_licenseList[0] = BeaconAboutLicense(this);
    p->_licenseList[0].setLicenseFromPath(pathToFile);
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::addLicenseTextFile(const QString &pathToFile)
{
    BeaconAboutLicense &firstLicense = p->_licenseList[0];
    BeaconAboutLicense newLicense(this);
    newLicense.setLicenseFromPath(pathToFile);
    if(p->_licenseList.count() ==1 && firstLicense.p->_licenseKey == BeaconAboutLicense::Unknown){
        firstLicense = newLicense;
    }else{
        p->_licenseList.append(newLicense);
    }
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setComponentName(const QString &componentName)
{
    p->_componentName = componentName;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setDisplayName(const QString &_displayName)
{
    p->_displayName = _displayName;
    p->_internalProgramName = _displayName.toUtf8();
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setOcsProvider(const QString &ocsProviderUrl)
{
    p->_ocsProviderUrl = ocsProviderUrl;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setVersion(const QByteArray &version)
{
    p->_version = version;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setShortDescription(const QString &shortDescription)
{
    p->_shortDescription = shortDescription;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setLicense(BeaconAboutLicense::LicenseKey licenseKey)
{
    return setLicense(LicenseKey,BeaconAboutLIcense::OnlyThisVersion);
}

BeaconApplicationInfo &BeaconApplicationInfo::setLicense(BeaconAboutLicense::licenseKey licenseKey,
                                                         BeaconAboutLicense::VersionRestriction versionRestriction)
{
    p->_licenseList[0] = BeaconAboutLicense(licenseKey,versionRestriction,this);
    return *this;
}   

BeaconApplicationInfo &BeaconApplicationInfo::addLicense(BeaconAboutLicense::LicenseKey licenseKey)
{
    return addLicense(LicenseKey,BeaconAboutLIcense::OnlyThisVersion);
}

BeaconApplicationInfo &BeaconApplicationInfo::addLicense(BeaconAboutLicense::licenseKey licenseKey,
                                                         BeaconAboutLicense::VersionRestriction versionRestriction)
{
    BeaconAboutLicense &firstLicense = p->_licenseList[0];
    if (p->_licenseList.count() == 1 && firstLicense.p->_licenseKey == BeaconAboutLicense::Unknown) {
        firstLicense = BeaconAboutLicense(licenseKey, versionRestriction, this);
    } else {
    p->_licenseList[0] = BeaconAboutLicense(licenseKey,versionRestriction,this);
    }
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setCopyrightStatement(const QString &copyrightStatement)
{
    p->_copyrightStatement = copyrightStatement;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setOtherText(const QString &otherText)
{
    p->_otherText = otherText;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setHomepage(const QString &homepage)
{
    p->_homepageAddress = homepage;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setBugAddress(const QByteArray &bugAddress)
{
    p->_bugAddress = bugAddress;
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setOrganizationDomain(const QByteArray &domain)
{
    p->organizationDomain = QString::fromLatin1(domain.data());
    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setProductName(const QByteArray &productName)
{
    p->productName = QString::fromUtf8(productName.data());
    return *this;
}

QString BeaconApplicationInfo::componentName() const
{
    return p->_componentName;
}

QString BeaconApplicationInfo::productName() const
{
    if (!p->productName.isEmpty()) {
        return p->productName;
    }
    return componentName();
}

QString BeaconApplicationInfo::displayName() const
{
    if (!p->_displayName.isEmpty()) {
        return p->_displayName;
    }
    return componentName();
}

QString BeaconApplicationInfo::programIconName() const
{
    return p->programIconName.isEmpty() ? componentName() : p->programIconName;
}

BeaconApplicationInfo &BeaconApplicationInfo::setProgramIconName(const QString &iconName)
{
    p->programIconName = iconName;
    return *this;
}

QVariant BeaconApplicationInfo::programLogo() const
{
    return p->programLogo;
}

BeaconApplicationInfo &BeaconApplicationInfo::setProgramLogo(const QVariant &image)
{
    p->programLogo = image;
    return *this;
}

QString BeaconApplicationInfo::ocsProviderUrl() const
{
    return p->_ocsProviderUrl;
}

QString BeaconApplicationInfo::version() const
{
    return QString::fromUtf8(p->_version.data());
}

QString BeaconApplicationInfo::shortDescription() const
{
    return p->_shortDescription;
}

QString BeaconApplicationInfo::homepage() const
{
    return p->_homepageAddress;
}

QString BeaconApplicationInfo::bugAddress() const
{
    return QString::fromUtf8(p->_bugAddress.constData());
}

QString BeaconApplicationInfo::organizationDomain() const
{
    return p->organizationDomain;
}

QList<BeaconAboutPerson> BeaconApplicationInfo::authors() const
{
    return p->_authorList;
}

QList<BeaconAboutPerson> BeaconApplicationInfo::credits() const
{
    return p->_creditList;
}

QList<BeaconAboutPerson> BeaconApplicationInfo::translators() const
{
    return p->_translatorList;
}

QList<BeaconAboutPerson> BeaconApplicationInfo::infoPrivate::parseTranslators(const QString &translatorName, const QString &translatorEmail)
{
    QList<BeaconAboutPerson> personList;
    if (translatorName.isEmpty() || translatorName == QStringLiteral("Your names")) {
        return personList;
    }

    const QStringList nameList(translatorName.split(QLatin1Char(',')));

    QStringList emailList;
    if (!translatorEmail.isEmpty() && translatorEmail != QStringLiteral("Your emails")) {
        emailList = translatorEmail.split(QLatin1Char(','), QString::KeepEmptyParts);
    }

    QStringList::const_iterator nit;
    QStringList::const_iterator eit = emailList.constBegin();

    for (nit = nameList.constBegin(); nit != nameList.constEnd(); ++nit) {
        QString email;
        if (eit != emailList.constEnd()) {
            email = *eit;
            ++eit;
        }

        personList.append(BeaconAboutPerson((*nit).trimmed(), email.trimmed(), true));
    }

    return personList;
}

QList<BeaconAboutPerson> BeaconApplicationInfo::translators() const
{
    return p->_translatorList;
}

QString BeaconApplicationInfo::aboutTranslationTeam()
{
    return QCoreApplication::translate(
               "BeaconApplicationInfo",
               "<p>BF is translated into this languages from source thanks to the work "
               "of the translation provider.</p>"
               "replace this with information about your translation team"
           );
}

QString BeaconApplicationInfo::otherText() const
{
    return p->_otherText;
}

QList<BeaconAboutLicense> BeaconApplicationInfo::licenses() const
{
    return p->_licenseList;
}

QString BeaconApplicationInfo::copyrightStatement() const
{
    return p->_copyrightStatement;
}

QString BeaconApplicationInfo::customAuthorPlainText() const
{
    return p->customAuthorPlainText;
}

QString BeaconApplicationInfo::customAuthorRichText() const
{
    return p->customAuthorRichText;
}

bool BeaconApplicationInfo::customAuthorTextEnabled() const
{
    return p->customAuthorTextEnabled;
}

BeaconApplicationInfo &BeaconApplicationInfo::setCustomAuthorText(const QString &plainText,
        const QString &richText)
{
    p->customAuthorPlainText = plainText;
    p->customAuthorRichText = richText;

    p->customAuthorTextEnabled = true;

    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::unsetCustomAuthorText()
{
    p->customAuthorPlainText = QString();
    p->customAuthorRichText = QString();

    p->customAuthorTextEnabled = false;

    return *this;
}

BeaconApplicationInfo &BeaconApplicationInfo::setDesktopFileName(const QString &desktopFileName)
{
    p->desktopFileName = desktopFileName;

    return *this;
}

QString BeaconApplicationInfo::desktopFileName() const
{
    return d->desktopFileName;
}

class BeaconApplicationInfoRegistry
{
public:
    BeaconApplicationInfoRegistry() : m_appData(nullptr) {}
    ~BeaconApplicationInfoRegistry()
    {
        delete m_appData;
    }
    BeaconApplicationInfoRegistry *m_appData;
};

Q_GLOBAL_STATIC(BeaconApplicationInfoRegistry, s_registry)

BeaconApplicationInfo BeaconApplicationInfo::applicationData()
{
    QCoreApplication *app = QCoreApplication::instance();

    BeaconApplicationInfo *aboutData = s_registry->m_appData;

    if (!aboutData) {
        aboutData = new BeaconApplicationInfo(QCoreApplication::applicationName(),
                                   QString(),
                                   QString());
        if (app) {
            aboutData->setOrganizationDomain(QCoreApplication::organizationDomain().toUtf8());
            aboutData->setVersion(QCoreApplication::applicationVersion().toUtf8());
            aboutData->setDisplayName(app->property("applicationDisplayName").toString());
            aboutData->setDesktopFileName(app->property("desktopFileName").toString());
        } else {
            //qCWarning(BeaconApplicationInfo) << "Could not initialize the properties of BeaconApplicationInfo::applicationData by the equivalent properties from Q*Application: no app instance (yet) existing.";
        }

        s_registry->m_appData = aboutData;
    } else {
        // check if in-sync with Q*Application metadata, as their setters could have been called
        // after the last BeaconApplicationInfo::setApplicationData, with different values
        /*warnIfOutOfSync("BeaconApplicationInfo::applicationData().componentName", aboutData->componentName(),
                        "QCoreApplication::applicationName", QCoreApplication::applicationName());
        warnIfOutOfSync("BeaconApplicationInfo::applicationData().version", aboutData->version(),
                        "QCoreApplication::applicationVersion", QCoreApplication::applicationVersion());
        warnIfOutOfSync("BeaconApplicationInfo::applicationData().organizationDomain", aboutData->organizationDomain(),
                        "QCoreApplication::organizationDomain", QCoreApplication::organizationDomain());*/
        if (app) {
            /*warnIfOutOfSync("BeaconApplicationInfo::applicationData().displayName", aboutData->displayName(),
                            "QGuiApplication::applicationDisplayName", app->property("applicationDisplayName").toString());
            warnIfOutOfSync("BeaconApplicationInfo::applicationData().desktopFileName", aboutData->desktopFileName(),
                            "QGuiApplication::desktopFileName", app->property("desktopFileName").toString());*/
        }
    }

    return *aboutData;
}

void BeaconApplicationInfo::setApplicationData(const BeaconApplicationInfo &aboutData)
{
    if (s_registry->m_appData) {
        *s_registry->m_appData = aboutData;
    } else {
        s_registry->m_appData = new BeaconApplicationInfo(aboutData);
    }

    QCoreApplication *app = QCoreApplication::instance();
    if (app) {
        app->setApplicationVersion(aboutData.version());
        app->setApplicationName(aboutData.componentName());
        app->setOrganizationDomain(aboutData.organizationDomain());
        app->setProperty("applicationDisplayName", aboutData.displayName());
        app->setProperty("desktopFileName", aboutData.desktopFileName());
    } else {
        //qCWarning(BeaconApplicationInfo) << "Could not initialize the equivalent properties of Q*Application: no instance (yet) existing.";
    }
}
