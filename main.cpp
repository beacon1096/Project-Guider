#include "MainWindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QThread>
#include "BeaconCompilerBackend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::addLibraryPath("./plugins");
    a.setOrganizationName(MainInfo::mainDev);
    a.setApplicationName(MainInfo::componentName);
    QSplashScreen splash;
    splash.setPixmap(QPixmap(":/Resources/Pics/Splash/Splash.jpg"));
    splash.showMessage("Initializing arguments");
    splash.show();

    splash.showMessage("Testing Compilers");
    BeaconCompilerBackend cbTest;
    int t=cbTest.compilerValidation();
    if(t==0){
        qDebug() << "gcc & g++ tested successfully";
    }
    else{
        splash.showMessage("Configuring Compilers");
        cbTest.configureCompilerPath(t);
    }
    splash.showMessage("Constructing Layout");
    //QThread::msleep(2000);
    MainWindow w;
    w.setWindowTitle(MainInfo::displayName);
    splash.finish(&w);
    w.show();

    return a.exec();
}
