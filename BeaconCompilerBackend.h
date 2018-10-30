#ifndef BEACONCOMPILERBACKEND_H
#define BEACONCOMPILERBACKEND_H

#include <QObject>
#include <QProcess>
#include <QTemporaryFile>
#include <QDir>
#include <QCoreApplication>
#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QDebug>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QToolButton>
#include <QTextBrowser>
#include <QMessageBox>
#include "BeaconPlatformInfo.h"
#include "BeaconFileIO.h"
#include "BeaconExternalProgram.h"

class BeaconCompilerBackend : public QObject
{
    Q_OBJECT
public:
    explicit BeaconCompilerBackend(QObject *parent = nullptr);
    BeaconExternalProgram gpp,gcc;
    int compilerValidation();
    bool configureCompilerPath(int lastError);
    bool compile();
    QProcess::ExitStatus lastCompileStatus;
    int lastCompileResult;
    QString latestCompileLog;
signals:
    void compileInfoUpdated(QString content);
public slots:
    void _compileInfoUpdated(QString content);
    void compileEnded(int result,QProcess::ExitStatus status);
    void compileStart(QString filePath, QString executable, QTextBrowser *target);
};
class BeaconCompilerSetupInterface : public QDialog{
    Q_OBJECT
public:
    explicit BeaconCompilerSetupInterface(int errorCode,QObject *parent = nullptr);
    QLabel *information;
    QLabel *gcc,*gpp;
    QLineEdit *gccL,*gppL;
    QToolButton *gccS,*gppS;
    QPushButton *confirm;
    QHBoxLayout *gccHL,*gppHL;
    QVBoxLayout *total;
public slots:
    void confirmClicked();
    void gccSClicked();
    void gppSClicked();
};

#endif // BEACONCOMPILERBACKEND_H
