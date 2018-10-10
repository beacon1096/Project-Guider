#include "BeaconFileIO.h"

BeaconFileIO::BeaconFileIO(QObject *parent) : QObject(parent)
{

}
bool BeaconFileIO::openFile(QFile& file,QString name,QChar IOMode){
    bool res=false;
    file.setFileName(name);
    if(IOMode=='r'){
        res=file.open(QIODevice::ReadOnly | QIODevice::Text);
    }
    if(IOMode=='w'){
        res=file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    }
    return res;
}
void BeaconFileIO::bundleIO(QFile& file,QTextStream& str){
    str.setDevice(&file);
}
QString BeaconFileIO::readFileContent(QString fileName){
    QFile file(fileName);
    if(!openFile(file,fileName,'r'))return QStringLiteral("*/*Plasma File General Error*/*");
    QTextStream inputStream(&file);
    QString res;
    while(!inputStream.atEnd()){
        res.append(inputStream.readAll());
    }
    return res;
}
bool BeaconFileIO::saveFileContent(QString fileName,QString content){
    QFile file(fileName);
    if(!openFile(file,fileName,'w'))return false;
    QTextStream outputStram(&file);
    outputStram<<content;
    return true;
}
