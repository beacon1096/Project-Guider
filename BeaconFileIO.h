#ifndef BEACONFILEIO_H
#define BEACONFILEIO_H

#include <QObject>
#include <QFile>
#include <QTextStream>

class BeaconFileIO : public QObject
{
    Q_OBJECT
public:
    explicit BeaconFileIO(QObject *parent = nullptr);
    static bool openFile(QFile& file,QString name,QChar IOMode);
    static void bundleIO(QFile& file,QTextStream& str);
    static QString readFileContent(QString fileName);
    static bool saveFileContent(QString fileName,QString content);

signals:

public slots:
};

#endif // BEACONFILEIO_H
