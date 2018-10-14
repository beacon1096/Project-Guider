#ifndef BEACONAPPLICATIONINFOOLD_H
#define BEACONAPPLICATIONINFOOLD_H

#include <QObject>
#include <QDate>
#include <QTime>
#include "MainInfo.h"

class BeaconApplicationInfoOld : public QObject
{
    Q_OBJECT
public:
    explicit BeaconApplicationInfoOld(QObject *parent = nullptr);
        QDate buildDate;
        QTime buildTime;
        QString componentName;
        QString displayName;
        QString version;
        QString buildType;
        QString shortDescription;
        QString copyrightStatement;
        QString homepage;
        QString license;
        QString bugAddress;
        QString ocsProvider;
        QString programLogo;
        QString versionOutput;
        QString otherText;
        void setComponentName(QString target);
        void setVersion(QString target);
        void setShortDescription(QString target);
        void setCopyrightStatement(QString target);
        void setHomepage(QString target);
        void setBuildType(QString target);
        void setBugAddress(QString target);
        void setLicense(QString target);
        void setDisplayName(QString target);
        void setOcsProvider(QString target);
        void setProgramLogo(QString target);
        void setVersionOutput(QString target);
        void setOtherText(QString target);
signals:

public slots:
};

#endif // BEACONAPPLICATIONINFO_H
