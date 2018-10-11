#include "MainInfo.h"

MainInfo::MainInfo(QObject *parent) : QObject(parent)
{
    plugins.append(BeaconPluginInfo(QString(tr("BeaconAboutInterface")),QString("1.0")));
    plugins.append(BeaconPluginInfo(QString(tr("BeaconApplicationInfo")),QString("1.0")));
    plugins.append(BeaconPluginInfo(QString(tr("BeaconCompilerBackend")),QString("1.0")));
    plugins.append(BeaconPluginInfo(QString(tr("BeaconExternalProgram")),QString("1.0")));
    plugins.append(BeaconPluginInfo(QString(tr("BeaconCodeProperty")),QString("1.0")));
    plugins.append(BeaconPluginInfo(QString(tr("BeaconPlatformInfo")),QString("1.0")));
    plugins.append(BeaconPluginInfo(QString(tr("BeaconPluginInfo")),QString("1.0")));
    plugins.append(BeaconPluginInfo(QString(tr("BeaconFileIO")),QString("1.0")));
}
QString MainInfo::componentName=QString("Beacon-CC");
QString MainInfo::displayName=QString("GUIDER");
QString MainInfo::version=QString("0.01");
QString MainInfo::shortDescription=QString("GAIT Universal IDE Refreshed\nUnder construction");
QString MainInfo::copyrightStatement=QString("(c) 2018 beacon1096");
QString MainInfo::homepage=QString("beacon1096.github.io");
QString MainInfo::license=QString("LGPL V3");
QString MainInfo::bugAddress=QString("beacon1096@outlook.com");
QString MainInfo::ocsProvider=QString("Github");
QString MainInfo::programLogo=QString(":/Resources/Pics/Beacon.png");
QString MainInfo::otherText=QString("DBGV Credential");
QString MainInfo::buildType=QString("In-Dev");
QString MainInfo::beaconFrameworkVersion=QString("1.0");
QString MainInfo::theme=QString("breath");
QString MainInfo::mainDev=QString("Beacon1096");
MainInfo mainInfo;
