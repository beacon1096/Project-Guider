#ifndef BEACONAPPLICATIONINFO_H
#define BEACONAPPLICATIONINFO_H

#include <QObject>
#include <QSharedData>

class QVarient;
class BeaconApplicationInfo;
class BeaconAboutPerson : public QObject{
    Q_OBJECT
public:
    explicit BeaconAboutPerson(const QString name,
                               const QString task=QString(),
                               const QString emailAddress=QString(),
                               const QString homePage=QString(),
                               const QString oscUsername=QString());
    BeaconAboutPerson(const BeaconAboutPerson &other);
    ~BeaconAboutPerson();
    BeaconAboutPerson &operator=(const BeaconAboutPerson &other);
    QString name();
    QString task();
    QString emailAddress();
    QString homePage();
    QString oscUsername();
private:
    class personPrivate;
    personPrivate *p;
};
class BeaconAboutLicense : public QObject{
    Q_OBJECT
public:
    enum LicenseKey {
            Custom = -2,
            File = -1,
            Unknown = 0,
            GPL  = 1,
            GPL_V2 = 1,
            LGPL = 2,
            LGPL_V2 = 2,
            BSDL = 3,
            Artistic = 4,
            QPL = 5,
            QPL_V1_0 = 5,
            GPL_V3 = 6,
            LGPL_V3 = 7,
            LGPL_V2_1 = 8
        };
    enum NameFormat {
            ShortName,
            FullName
        };
    enum VersionRestriction {
            OnlyThisVersion,
            OrLaterVersions
        };
    BeaconAboutLicense(const BeaconAboutLicense &other);
    ~BeaconAboutLicense();
    BeaconAboutLicense &operator=(const BeaconAboutLicense &other);
    QString text();
    QString name(BeaconAboutLicense::NameFormat formatName);
    BeaconAboutLicense::LicenseKey key();
private:
    explicit BeaconAboutLicense(enum BeaconAboutLicense::LicenseKey licenseType,
                                enum BeaconAboutLicense::VersionRestriction versionRestriction,
                                const BeaconApplicationInfo *aboutInfo);
    explicit BeaconAboutLicense(enum BeaconAboutLicense::LicenseKey lisenceType,
                                const BeaconApplicationInfo *aboutInfo);
    explicit BeaconAboutLicense(const BeaconApplicationInfo *aboutInfo);
    void setLicenseFromFile(const QString &pathToFile);
    void setLicenseFromText(const QString &pathToText);

    class licensePrivate;
    QSharedDataPointer<licensePrivate> p;
};

class BeaconApplicationInfo : public QObject
{
    Q_OBJECT
public:
    static BeaconApplicationInfo applicationData();
    static void setApplicationData();
    static void registerPluginData(const BeaconApplicationInfo &aboutData);
public:
    BeaconApplicationInfo(const QString &componentName,
                          const QString &displayName,
                          const QString &version,
                          const QString &shortDescription,
                          enum BeaconAboutLicense::LicenseKey licenseType,
                          const QString &copyrightStatement = QString(),
                          const QString &otherText = QString(),
                          const QString &homePageAddress = QString(),
                          const QString &bugAddress = QStringLiteral("beacon1096@outlook.com")
            );
    BeaconApplicationInfo(const QString &componentName,
                          const QString &displayName,
                          const QString &version
                          );
    BeaconApplicationInfo(const BeaconApplicationInfo &other);
    BeaconApplicationInfo &operator=(const BeaconApplicationInfo &other);
    ~BeaconApplicationInfo();
    BeaconApplicationInfo &addAuthor(const QString &name,
                                     const QString &task = QString(),
                                     const QString &emailAddress = QString(),
                                     const QString &webAddress = QString(),
                                     const QString &ocsUsername = QString());
    BeaconApplicationInfo &addCredit(const QString &name,
                             const QString &task = QString(),
                             const QString &emailAddress = QString(),
                             const QString &webAddress = QString(),
                             const QString &ocsUsername = QString());
    BeaconApplicationInfo &setLicenseText(const QString &license);
    BeaconApplicationInfo &addLicenseText(const QString &license);
    BeaconApplicationInfo &setLicenseTextFile(const QString &file);
    BeaconApplicationInfo &addLicenseTextFile(const QString &file);
    BeaconApplicationInfo &setComponentName(const QString &componentName);
    BeaconApplicationInfo &setDisplayName(const QString &displayName);
    BeaconApplicationInfo &setProgramLogo(const QVariant &image);
    BeaconApplicationInfo &setOcsProvider(const QString &providerUrl);
    BeaconApplicationInfo &setVersion(const QString &version);
    BeaconApplicationInfo &setShortDescription(const QString &shortDescription);
    BeaconApplicationInfo &setLicense(BeaconAboutLicense::LicenseKey licenseKey);
    BeaconApplicationInfo &setLicense(BeaconAboutLicense::LicenseKey licenseKey,
                                      BeaconAboutLicense::VersionRestriction versionRestriction);
    BeaconApplicationInfo &addLicense(BeaconAboutLicense::LicenseKey licenseKey);
    BeaconApplicationInfo &addLicense(BeaconAboutLicense::LicenseKey licenseKey,
                                      BeaconAboutLicense::VersionRestriction versionRestriction);
    BeaconApplicationInfo &setCopyrightStatement(const QString &copyrightStatment);
    BeaconApplicationInfo &setOtherText(const QString &otherText);
    BeaconApplicationInfo &sethomePage(const QString &homePage);
    BeaconApplicationInfo &setBugAddress(const QString &bugAddress);
    BeaconApplicationInfo &setOrganizationDomain(const QByteArray &domain);
    BeaconApplicationInfo &setProductName(const QByteArray &name);
    QString componentName();
    QString productName();
    QString displayName();
    QString organizationName();
    QString programIconName();
    QVarient programLogo();
    QString ocsProviderUrl();
    QString version();
    QString shortDescription();
    QString copyrightStatement();
    QString otherText();
    QString homePage();
    QString bugAddress();
    QList<BeaconAboutPerson> authors();
    QList<BeaconAboutPerson> credits();
    QList<BeaconAboutLicense> licenses();
    QString customAuthorHeaderText();
    bool customAuthorHeaderTextEnable();
    BeaconApplicationInfo &setCustomAuthorText(const QString &plainText,
                                               const QString &richText);
    BeaconApplicationInfo &unsetCustomAuthorText();
    BeaconApplicationInfo &setLinuxDesktopFileName(const QString &desktopFilePath);
    QString desktopFileName();
signals:

public slots:
};

#endif // BEACONAPPLICATIONINFO_H
