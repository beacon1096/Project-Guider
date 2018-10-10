#include "BeaconPlatformInfo.h"

BeaconPlatformInfo::BeaconPlatformInfo(QObject *parent) : QObject(parent)
{
}
    QString BeaconPlatformInfo::BuildABI=QSysInfo::buildAbi();
    QString BeaconPlatformInfo::BuildCPUArch=QSysInfo::buildCpuArchitecture();
    QString BeaconPlatformInfo::CuCPUArch=QSysInfo::currentCpuArchitecture();
    QString BeaconPlatformInfo::Kernel=QSysInfo::kernelType();
    QString BeaconPlatformInfo::KernelVersion=QSysInfo::kernelVersion();
    QString BeaconPlatformInfo::HostName=QSysInfo::machineHostName();
    QString BeaconPlatformInfo::OSFormattedProductName=QSysInfo::prettyProductName();
    QString BeaconPlatformInfo::OSProductName=QSysInfo::productType();
    QString BeaconPlatformInfo::OSProductVersion=QSysInfo::productVersion();
    #ifdef Q_OS_LINUX
    QString BeaconPlatformInfo::OS=QString("Linux");
    bool BeaconPlatformInfo::isLinux=true;
    bool BeaconPlatformInfo::isWindows=false;
    bool BeaconPlatformInfo::isMacos=false;
    QString BeaconPlatformInfo::windowingSystem=QString("xcb");
    #endif
    #ifdef Q_OS_UNIX
        #ifndef Q_OS_LINUX
        QString BeaconPlatformInfo::OS=QString("UNIX");
        bool BeaconPlatformInfo::isLinux=true;
        bool BeaconPlatformInfo::isWindows=false;
        bool BeaconPlatformInfo::isMacos=false;
        QString BeaconPlatformInfo::windowingSystem=QString("xcb");
        #endif
    #endif
    #ifdef Q_WS_X11
    QString BeaconPlatformInfo::windowingSystem="xcb";
    #endif
    #ifdef Q_OS_MACOS
    QString BeaconPlatformInfo::OS=QString("MACOS");
    bool BeaconPlatformInfo::isMacos=true;
    bool BeaconPlatformInfo::isWindows=false;
    bool BeaconPlatformInfo::isLinux=false;
    #endif
    #ifdef Q_OS_DARWIN
        #ifndef Q_OS_MACOS
        QString BeaconPlatformInfo::OS=QString("DARWIN");
        bool BeaconPlatformInfo::isMacos=true;
        bool BeaconPlatformInfo::isWindows=false;
        bool BeaconPlatformInfo::isLinx=false;
        #endif
    #endif
    #ifdef Q_OS_NETBSD
    QString BeaconPlatformInfo::OS=QString("NETBSD");
    #endif
    #ifdef Q_OS_OPENBSD
    QString BeaconPlatformInfo::OS=QString("OPENBSD");
    #endif
    #ifdef Q_OS_SOLARIS
    QString BeaconPlatformInfo::OS=QString("SOLARIS");
    #endif
    #ifdef Q_OS_WIN64
    QString BeaconPlatformInfo::OS=QString("WIN64");
    QString BeaconPlatformInfo::windowingSystem="windows";
    bool BeaconPlatformInfo::isWindows=true;
    bool BeaconPlatformInfo::isLinux=false;
    bool BeaconPlatformInfo::isMacos=false;
    #endif
    #ifdef Q_OS_WIN32
        #ifndef Q_OS_WIN64
        QString BeaconPlatformInfo::OS=QString("WIN32");
        QString BeaconPlatformInfo::windowingSystem="windows";
        bool BeaconPlatformInfo::isWindows=true;
        bool BeaconPlatformInfo::isLinux=false;
        bool BeaconPlatformInfo::isMacos=false;
        #endif
    #endif
    #ifdef Q_OS_WINRT
        #ifndef Q_OS_WIN32
            #ifndef Q_OS_WIN64
            QString BeaconPlatformInfo::OS=QString("WINRT");
            QString BeaconPlatformInfo::windowingSystem="windows";
            bool BeaconPlatformInfo::isWindows=true;
            bool BeaconPlatformInfo::isLinux=false;
            bool BeaconPlatformInfo::isMacos=false;
            #endif
        #endif
    #endif
    #ifdef Q_OS_WIN
        #ifndef Q_OS_WINRT
            #ifndef Q_OS_WIN32
                #ifndef Q_OS_WIN64
                QString BeaconPlatformInfo::OS=QString("WIN");
                QString BeaconPlatformInfo::windowingSystem="windows";
                bool BeaconPlatformInfo::isWindows=true;
                bool BeaconPlatformInfo::isLinux=false;
                bool BeaconPlatformInfo::isMacos=false;
                #endif
            #endif
        #endif
    #endif
    #ifdef Q_OS_TVOS
     QString BeaconPlatformInfo::OS=QString("TVOS");
    #endif
    #ifdef Q_OS_IOS
     QString BeaconPlatformInfo::OS=QString("IOS");
    #endif
    #ifdef Q_OS_CYGWIN
     QString BeaconPlatformInfo::OS=QString("CYGWIN");
    #endif
    #ifdef Q_OS_ANDROID
     QString BeaconPlatformInfo::OS=QString("ANDROID");
    #endif

