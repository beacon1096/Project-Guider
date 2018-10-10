#ifndef BEACONPLUGININFO_H
#define BEACONPLUGININFO_H

#include <QObject>

class BeaconPluginInfo : public QObject
{
    Q_OBJECT
public:
    explicit BeaconPluginInfo(QObject *parent = nullptr);
    //explicit
    BeaconPluginInfo(QString name,QString version);
    //explicit
    BeaconPluginInfo(QString name,int version);
    //explicit
    BeaconPluginInfo(const BeaconPluginInfo &target);
    QString pluginName;
    QString pluginVersion;
    void operator=(const BeaconPluginInfo &target)const;
signals:

public slots:
};

#endif // BEACONPLUGININFO_H
