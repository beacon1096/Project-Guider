#ifndef MAININFO_H
#define MAININFO_H

#include <QObject>
#include "BeaconPluginInfo.h"

class MainInfo : public QObject
{
    Q_OBJECT
public:
    explicit MainInfo(QObject *parent = nullptr);
    static QString componentName;
    static QString displayName;
    static QString version;
    static QString shortDescription;
    static QString copyrightStatement;
    static QString homepage;
    static QString license;
    static QString bugAddress;
    static QString ocsProvider;
    static QString programLogo;
    static QString versionOutput;
    static QString otherText;
    static QString buildType;
    static QString beaconFrameworkVersion;
    static QString theme;
    static QString mainDev;
    QList<BeaconPluginInfo> plugins;
signals:

public slots:
};
extern MainInfo mainInfo;
#endif // MAININFO_H
