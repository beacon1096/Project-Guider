#include "BeaconCompilerBackend.h"

BeaconCompilerBackend::BeaconCompilerBackend(QObject *parent) : QObject(parent)
{
    QSettings settings;
    if(!settings.value("gccPath").toString().isEmpty()){
        gcc.setProgram(settings.value("gccPath").toString());
        gpp.setProgram(settings.value("gppPath").toString());
    }
    else if(BeaconPlatformInfo::isLinux || BeaconPlatformInfo::isMacos){
        gcc.setProgram("/usr/bin/gcc");
        gpp.setProgram("/usr/bin/g++");
        settings.setValue("gccPath","/usr/bin/gcc");
        settings.setValue("gppPath","/usr/bin/g++");
    }
    else{
        gcc.setProgram("C:/MinGW/bin/gcc.exe");
        gpp.setProgram("C:/MinGW/bin/g++.exe");
        settings.setValue("gccPath","C:/MinGW/bin/gcc.exe");
        settings.setValue("gppPath","C:/MinGW/bin/g++.exe");
    }
    connect(&gcc,SIGNAL(programExited(int,QProcess::ExitStatus)),this,SLOT(compileEnded(int,QProcess::ExitStatus)));
    connect(&gpp,SIGNAL(programExited(int,QProcess::ExitStatus)),this,SLOT(compileEnded(int,QProcess::ExitStatus)));
}
bool BeaconCompilerBackend::compilerValidation(){
    QString cCodeName=QDir::tempPath()+QDir::separator()+QCoreApplication::applicationName()+"_XXXXXX."+"c";
    QString cppCodeName=QDir::tempPath()+QDir::separator()+QCoreApplication::applicationName()+"_XXXXXX."+"cpp";
    QFile c(gcc.programPath),cpp(gpp.programPath);
    if(!c.exists() || !cpp.exists())return false;
    QTemporaryFile ct(cCodeName);
    if(ct.open()){
        BeaconFileIO::saveFileContent(ct.fileName(),BeaconFileIO::readFileContent(":/Resources/Code/test.c"));
        QStringList arg;
        arg.append(ct.fileName());
        gcc.program.setArguments(arg);
        gcc.startProgram();
        gcc.program.waitForFinished();
        QString result=gcc.logOut;
        qDebug() << "gcc test result:" << result;
        qDebug() << "RT result:(1)" << lastCompileResult << ",(2)" << lastCompileStatus;
        if(lastCompileResult!=0)return false;
        if(!result.isEmpty())return false;
    }
    QTemporaryFile cppt(cppCodeName);
    if(cppt.open()){
        BeaconFileIO::saveFileContent(cppt.fileName(),BeaconFileIO::readFileContent(":/Resources/Code/test.cpp"));
        QStringList arg;
        arg.append(cppt.fileName());
        gpp.program.setArguments(arg);
        gpp.startProgram();
        gpp.program.waitForFinished();
        QString result=gpp.logOut;
        qDebug() << "g++ test result:" << result;
        qDebug() << "RT result:(1)" << lastCompileResult << ",(2)" << lastCompileStatus;
        if(lastCompileResult!=0)return false;
        if(!result.isEmpty())return false;
    }
    return true;
}
bool BeaconCompilerBackend::configureCompilerPath(){
    BeaconCompilerSetupInterface bcsi;
    bcsi.exec();
    return true;
}
void BeaconCompilerBackend::compileEnded(int result,QProcess::ExitStatus status){
    lastCompileResult = result;
    lastCompileStatus = status;
}
void BeaconCompilerBackend::compileStart(QString filePath,QString executable){
    QString suffix=filePath.split(".").last();
    if(suffix=="c"){
        QStringList arg;
        arg.append(filePath);
        arg.append("-o");
        arg.append(executable);
        gcc.clearLog();
        gcc.setArguments(arg);
        qDebug() << "executing gcc " << arg;
        gcc.startProgram();
        gcc.program.waitForFinished();
        qDebug() << "result:(1)" << lastCompileResult << ",(2)" << lastCompileStatus;
        qDebug() << "logs:" << gcc.logOut;
        latestCompileLog=gcc.logOut;

    }
    else if(suffix=="cpp"){
        QStringList arg;
        arg.append(filePath);
        arg.append("-o");
        arg.append(executable);
        gpp.clearLog();
        gpp.setArguments(arg);
        qDebug() << "executing g++ " << arg;
        gpp.startProgram();
        gpp.program.waitForFinished();
        qDebug() << "result:(1)" << lastCompileResult << ",(2)" << lastCompileStatus;
        qDebug() << "logs:" << gpp.logOut;
        latestCompileLog=gpp.logOut;
    }
}
BeaconCompilerSetupInterface::BeaconCompilerSetupInterface(QObject *parent) : QDialog(){
    gccHL = new QHBoxLayout;gppHL = new QHBoxLayout;
    total = new QVBoxLayout;
    gcc = new QLabel("GCC:");
    gpp = new QLabel("G++:");
    gccL = new QLineEdit();
    gppL = new QLineEdit();
    gccS = new QToolButton();
    gppS = new QToolButton();
    gccS->setText("...");
    gppS->setText("...");
    confirm = new QPushButton("OK");
    QSettings settings;
    gccL->setText(settings.value("gccPath").toString());
    gppL->setText(settings.value("gppPath").toString());
    connect(gccS,SIGNAL(clicked()),this,SLOT(gccSClicked()));
    connect(gppS,SIGNAL(clicked()),this,SLOT(gppSClicked()));
    connect(confirm,SIGNAL(clicked()),this,SLOT(confirmClicked()));
    gccHL->addWidget(gcc);gccHL->addWidget(gccL);gccHL->addWidget(gccS);
    gppHL->addWidget(gpp);gppHL->addWidget(gppL);gppHL->addWidget(gppS);
    total->addLayout(gccHL);total->addLayout(gppHL);total->addWidget(confirm);
    this->setLayout(total);
}
void BeaconCompilerSetupInterface::gppSClicked(){
    QString path;
    if(BeaconPlatformInfo::isWindows)
        path = QFileDialog::getOpenFileName(this,tr("Select G++ Path"),".","g++.exe");
    else
        path = QFileDialog::getOpenFileName(this,tr("Select G++ Path"),".","g++");
    gppL->setText(path);
}
void BeaconCompilerSetupInterface::gccSClicked(){
    QString path;
    if(BeaconPlatformInfo::isWindows)
        path = QFileDialog::getOpenFileName(this,tr("Select GCC Path"),".","gcc.exe");
    else
        path = QFileDialog::getOpenFileName(this,tr("Select GCC Path"),".","gcc");
    gccL->setText(path);
    QString gppPath=path;
    gppPath.replace(gppPath.lastIndexOf("gcc"),3,"g++");
    QFile gppTest(gppPath);
    if(gppTest.exists())
        gppL->setText(gppPath);
}
void BeaconCompilerSetupInterface::confirmClicked(){
    QSettings settings;
    settings.setValue("gccPath",this->gccL->text());
    settings.setValue("gppPath",this->gppL->text());
    this->close();
}
