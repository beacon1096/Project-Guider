#ifndef BeaconCodeProperty_H
#define BeaconCodeProperty_H

#include <QObject>

class BeaconCodeProperty : public QObject
{
    Q_OBJECT
public:
    //explicit BeaconCodeProperty(QObject *parent = nullptr);
    explicit BeaconCodeProperty(QString filePathArg = "");//,QObject *parent=nullptr);
    explicit BeaconCodeProperty(const BeaconCodeProperty &source);
    QString fileName,filePath;
    QString executablePath;
    bool changed;
    bool updateChangedStatus(bool state);
    void operator=(const BeaconCodeProperty &source);
    void setProperty(BeaconCodeProperty &source);
    void setProperty(QString &source);
signals:

public slots:
};

#endif // BeaconCodeProperty_H
