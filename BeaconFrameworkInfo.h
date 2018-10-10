#ifndef BEACONFRAMEWORKINFO_H
#define BEACONFRAMEWORKINFO_H

#include <QObject>
#include <QDate>
#include <QTime>

class BeaconFrameworkInfo : public QObject
{
    Q_OBJECT
public:
    explicit BeaconFrameworkInfo();
    static QDate buildDate;
    static QTime buildTime;
    static QString componentName;
    static QString displayName;
    static QString version;
    static QString buildType;
    static QString shortDescription;
    static QString copyrightStatement;
    static QString homepage;
    static QString license;
    static QString bugAddress;
    static QString ocsProvider;
    static QString programLogo;
    static QString versionOutput;
    static QString otherText;
};
#endif // BEACONFRAMEWORKINFO_H
