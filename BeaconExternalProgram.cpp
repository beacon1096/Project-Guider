#include "BeaconExternalProgram.h"

BeaconExternalProgram::BeaconExternalProgram(QObject *parent) : QObject(parent)
{
    connect(&program,SIGNAL(readyReadStandardOutput()),this,SLOT(programOutputUpdatedTriggered()));
    connect(&program,SIGNAL(readyReadStandardError()),this,SLOT(programErrorUpdatedTriggered()));
    connect(&program,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(sendProgramExited(int,QProcess::ExitStatus)));
}
bool BeaconExternalProgram::setProgram(QString path,QStringList argu){
    programPath=path;
    arguments=argu;
    program.setProgram(programPath);
    program.setArguments(arguments);
    programFile.setFileName(path);
    if(!programFile.exists())return false;
    return true;
}
void BeaconExternalProgram::clearLog(){
    this->logOut.clear();
    this->logOutDelta.clear();
    this->errorOut.clear();
    this->errorOutDelta.clear();
    this->standardOut.clear();
    this->standardOutDelta.clear();
}
void BeaconExternalProgram::setArguments(QStringList arg){
    program.setArguments(arg);
}
bool BeaconExternalProgram::startProgram(){
    program.start();
    if (!program.waitForStarted()){
        return false;
    }
    return true;
}
bool BeaconExternalProgram::startProgramDetached(){
    program.startDetached();
    if (!program.waitForStarted()){
        return false;
    }
    return true;
}
void BeaconExternalProgram::sendProgramExited(int result,QProcess::ExitStatus status){
    emit programExited(result,status);
}
void BeaconExternalProgram::programOutputUpdatedTriggered(){
    QByteArray ba = program.readAllStandardOutput();
    standardOut.append(ba);
    logOut.append(ba);
    standardOutDelta=ba;
    logOutDelta=ba;
    qDebug() << "[BEP]update:" << QString(ba);
    emit programOutputUpdated(ba);
    emit programLogUpdated(ba);
}
void BeaconExternalProgram::programErrorUpdatedTriggered(){
    QByteArray ba = program.readAllStandardError();
    errorOut.append(ba);
    logOut.append(ba);
    errorOutDelta=ba;
    logOutDelta=ba;
    emit programErrorUpdated(ba);
    emit programLogUpdated(ba);
}
