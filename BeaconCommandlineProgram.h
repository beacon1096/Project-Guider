#ifndef BEACONCOMMANDLINEPROGRAM_H
#define BEACONCOMMANDLINEPROGRAM_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include "BeaconExternalProgram.h"
#include "BeaconPlatformInfo.h"

class BeaconCommandlineProgram : public BeaconExternalProgram
{
    Q_OBJECT
public:
    explicit BeaconCommandlineProgram(QString platform=QString("auto"));
    void setArguments(QStringList arg);
    QStringList prefixArgument;
    QStringList suffixArgument;
    bool bashBased=false;
    bool manualHalt=false;

signals:

public slots:
};

#endif // BEACONCOMMANDLINEPROGRAM_H
