#ifndef BeaconCodeProperty_H
#define BeaconCodeProperty_H

#include <QObject>
#include <Qsci/qsciscintilla.h>
#include "BeaconPlatformInfo.h"

class BeaconEditorInfo : public QObject
{
    Q_OBJECT
public:
    //explicit BeaconCodeProperty(QObject *parent = nullptr);
    explicit BeaconEditorInfo(QString filePathArg = "");//,QObject *parent=nullptr);
    explicit BeaconEditorInfo(const BeaconEditorInfo &source);
    QString fileName,filePath;
    QString executablePath;
    QString suffix;
    QsciScintilla *editor;
    bool changed;
    bool updateChangedStatus(bool state);
    void operator=(const BeaconEditorInfo &source);
    void setProperty(BeaconEditorInfo &source);
    void setProperty(QString &source);
signals:

public slots:
private:
    void _genExecutablePath();
    void _genSuffix();
    void _genFileName();
};

#endif // BeaconCodeProperty_H
