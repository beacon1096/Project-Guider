#-------------------------------------------------
#
# Project created by QtCreator 2018-10-05T21:02:29
#
#-------------------------------------------------
# MainWindow 414
QT       += core gui widgets svg

TARGET = SapphireIDE
TEMPLATE = app

#windows:LIBS += -LC:/Qt/Qt5.11.1/5.11.1/msvc2017_64/lib -lqscintilla2_qt5
windows:LIBS += -LC:/msys64/mingw64/lib -lqscintilla2_qt5
linux:LIBS += -L/lib64 -lqscintilla2_qt5
macx:LIBS += -L/usr/local/Cellar/qt/5.11.2/lib -lqscintilla2_qt5

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    BeaconFileIO.cpp \
    BeaconCompilerBackend.cpp \
    BeaconExternalProgram.cpp \
    BeaconPlatformInfo.cpp \
    MainInfo.cpp \
    BeaconAboutInterface.cpp \
    BeaconPluginInfo.cpp \
    BeaconFrameworkInfo.cpp \
    BeaconQsciHelper.cpp \
    BeaconApplicationInfoOld.cpp \
    #BeaconApplicationInfo.cpp
    BeaconEditorInfo.cpp \
    BeaconEditorTab.cpp


HEADERS += \
        MainWindow.h \
    BeaconFileIO.h \
    BeaconCompilerBackend.h \
    BeaconExternalProgram.h \
    BeaconPlatformInfo.h \
    MainInfo.h \
    BeaconAboutInterface.h \
    BeaconPluginInfo.h \
    BeaconFrameworkInfo.h \
    BeaconQsciHelper.h \
    BeaconApplicationInfoOld.h \
    BeaconWindowsAero.h \
    BeaconEditorInfo.h \
    BeaconEditorTab.h
    #BeaconApplicationInfo.h


FORMS += \
        MainWindow.ui \
    BeaconAboutInterface.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


# DISTFILES += \
#    KDEFrameworks.pri

macx:INCLUDEPATH += /usr/local/Cellar/qt/5.11.2/include
macx:DEPENDPATH += /usr/local/Cellar/qt/5.11.2/include
