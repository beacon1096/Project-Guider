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
        if(BeaconPlatformInfo::isMacos){
            QMessageBox::warning(NULL, "Clang | GCC", tr("Please be noticed that macOS automatically links Clang to GCC.\nIf you wish to use GCC, please install it yourself and change the settings."), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
    else{
        gcc.setProgram("C:/MinGW/bin/gcc.exe");
        gpp.setProgram("C:/MinGW/bin/g++.exe");
        settings.setValue("gccPath","C:/MinGW/bin/gcc.exe");
        settings.setValue("gppPath","C:/MinGW/bin/g++.exe");
    }
    connect(&gcc,SIGNAL(programExited(int,QProcess::ExitStatus)),this,SLOT(compileEnded(int,QProcess::ExitStatus)));
    connect(&gpp,SIGNAL(programExited(int,QProcess::ExitStatus)),this,SLOT(compileEnded(int,QProcess::ExitStatus)));
    connect(&gcc,SIGNAL(programLogUpdated(QString)),this,SLOT(_compileInfoUpdated(QString)));
    connect(&gpp,SIGNAL(programLogUpdated(QString)),this,SLOT(_compileInfoUpdated(QString)));
}
void BeaconCompilerBackend::_compileInfoUpdated(QString Content){
    qDebug() << "[BeaconCompilerBackend]_cIU:" << Content;
    emit compileInfoUpdated(Content);
}
int BeaconCompilerBackend::compilerValidation(){
    QString cCodeName=QDir::tempPath()+QDir::separator()+QCoreApplication::applicationName()+"_XXXXXX."+"c";
    QString cppCodeName=QDir::tempPath()+QDir::separator()+QCoreApplication::applicationName()+"_XXXXXX."+"cpp";
    QFile c(gcc.programPath),cpp(gpp.programPath);
    if(!c.exists() || !cpp.exists())return -1;
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
        if(lastCompileResult!=0)return -2;
        if(!result.isEmpty())return -2;
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
        if(lastCompileResult!=0)return -2;
        if(!result.isEmpty())return -2;
    }
    return 0;
}
bool BeaconCompilerBackend::configureCompilerPath(int lastError){
    BeaconCompilerSetupInterface bcsi(lastError);
    bcsi.exec();
    return !compilerValidation();
}
void BeaconCompilerBackend::compileEnded(int result,QProcess::ExitStatus status){
    lastCompileResult = result;
    lastCompileStatus = status;
}
void BeaconCompilerBackend::compileStart(QString filePath,QString executable,QTextBrowser* target){
    QString suffix=filePath.split(".").last();
    if(suffix=="c"){
        QStringList arg;
        arg.append(filePath);
        arg.append("-o");
        arg.append(executable);
        arg.append("-Wall");
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
        arg.append("-Wall");
        gpp.clearLog();
        gpp.setArguments(arg);
        qDebug() << "executing g++ " << arg;
        qDebug() << "compile command:[" << gpp.program.program() << " " << arg;
        gpp.startProgram();
        gpp.program.waitForFinished();
        qDebug() << "result:(1)" << lastCompileResult << ",(2)" << lastCompileStatus;
        qDebug() << "logs:" << gpp.logOut;
        latestCompileLog=gpp.logOut;
    }
}
BeaconCompilerSetupInterface::BeaconCompilerSetupInterface(int errorCode,QObject *parent) : QDialog(){
    information = new QLabel;
    QSettings settings;
    if(errorCode==-1)information->setText(QString(tr("Could not find compiler in default Location.").append("\n").append(tr("Please specify where it is."))));
    if(errorCode==-2)information->setText(QString(tr("Your compiler is unable to compile a simple test program.")).append("\n").append(tr("Please specify a working one.")));
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
    gccL->setText(settings.value("gccPath").toString());
    gppL->setText(settings.value("gppPath").toString());
    connect(gccS,SIGNAL(clicked()),this,SLOT(gccSClicked()));
    connect(gppS,SIGNAL(clicked()),this,SLOT(gppSClicked()));
    connect(confirm,SIGNAL(clicked()),this,SLOT(confirmClicked()));
    total->addWidget(information);
    gccHL->addWidget(gcc);gccHL->addWidget(gccL);gccHL->addWidget(gccS);
    gppHL->addWidget(gpp);gppHL->addWidget(gppL);gppHL->addWidget(gppS);
    total->addLayout(gccHL);total->addLayout(gppHL);total->addWidget(confirm);
    this->setLayout(total);
}
void BeaconCompilerSetupInterface::gppSClicked(){
    QString path;
    if(BeaconPlatformInfo::isWindows)
        path = QFileDialog::getOpenFileName(this,tr("Select G++ Path"),"C:/","g++.exe");
    else
        path = QFileDialog::getOpenFileName(this,tr("Select G++ Path"),"/","");
    gppL->setText(path);
}
void BeaconCompilerSetupInterface::gccSClicked(){
    QString path;
    if(BeaconPlatformInfo::isWindows)
        path = QFileDialog::getOpenFileName(this,tr("Select GCC Path"),"C:/","gcc.exe");
    else
        path = QFileDialog::getOpenFileName(this,tr("Select GCC Path"),"/","");
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
