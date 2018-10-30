#ifndef BEACONEXTERNALPROGRAM_H
#define BEACONEXTERNALPROGRAM_H

#include <QObject>
#include <QFile>
#include <QProcess>

class BeaconExternalProgram : public QObject
{
    Q_OBJECT
public:
    explicit BeaconExternalProgram(QObject *parent = nullptr);
    QProcess program;
    QFile programFile;
    QString programPath;
    QStringList arguments;
    QByteArray standardOut,errorOut,logOut;
    QByteArray standardOutDelta,errorOutDelta,logOutDelta;
    bool setProgram(QString path,QStringList argu=QString("").split('.'));
    void setArguments(QStringList arg);
    bool startProgram();
    bool startProgramDetached();
    void clearLog();
signals:
    void programOutputUpdated(QString content);
    void programErrorUpdated(QString content);
    void programLogUpdated(QString content);
    void programExited(int result,QProcess::ExitStatus);
public slots:
    void sendProgramExited(int result,QProcess::ExitStatus status);
    void programOutputUpdatedTriggered();
    void programErrorUpdatedTriggered();
};

#endif // BEACONEXTERNALPROGRAM_H
