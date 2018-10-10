#ifndef BEACONPLATFORMINFO_H
#define BEACONPLATFORMINFO_H

#include <QObject>
#include <QSysInfo>

class BeaconPlatformInfo : public QObject
{
    Q_OBJECT
public:
    explicit BeaconPlatformInfo(QObject *parent = nullptr);
    static QString OS,Kernel,KernelVersion;
    static QString BuildABI,BuildCPUArch;
    static QString CuCPUArch;
    static QString HostName;
    static QString OSProductName,OSFormattedProductName;
    static QString OSProductVersion;
    static QString windowingSystem;
    static bool isWindows,isLinux,isMacos;
signals:

public slots:
};

#endif // BEACONPLATFORMINFO_H
