#-------------------------------------------------
#
# Project created by QtCreator 2018-10-05T21:02:29
#
#-------------------------------------------------

QT       += core gui widgets
QT       += KConfigCore KConfigGui KConfigWidgets
Qt       += KTextEditor
QT       += KCoreAddons KXmlGui KI18n KTextWidgets SonnetCore SonnetUi

TARGET = BeaconCppCreator
TEMPLATE = app

windows:LIBS += -LA:/Code/Qt/Qt5.11.1/5.11.1/msvc2017_64/lib -lqscintilla2_qt5
linux:LIBS += -L/lib64 -lqscintilla2_qt5

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
    BeaconCodeProperty.cpp \
    BeaconCompilerBackend.cpp \
    BeaconExternalProgram.cpp \
    BeaconPlatformInfo.cpp \
    BeaconApplicationInfo.cpp \
    MainInfo.cpp \
    BeaconAboutInterface.cpp \
    BeaconPluginInfo.cpp \
    BeaconFrameworkInfo.cpp \
    BeaconQsciHelper.cpp \


HEADERS += \
        MainWindow.h \
    BeaconFileIO.h \
    BeaconCompilerBackend.h \
    BeaconExternalProgram.h \
    BeaconPlatformInfo.h \
    BeaconApplicationInfo.h \
    MainInfo.h \
    BeaconAboutInterface.h \
    BeaconPluginInfo.h \
    BeaconFrameworkInfo.h \
    BeaconQsciHelper.h \
    BeaconCodeProperty.h


FORMS += \
        MainWindow.ui \
    BeaconAboutInterface.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

KF5_DIR = C:/CraftRoot

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5CoreAddons
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5CoreAddonsd
INCLUDEPATH += $$KF5_DIR/include/KF5/KCoreAddons
DEPENDPATH += $$KF5_DIR/include/KF5/KCoreAddons

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5I18n
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5I18nd
INCLUDEPATH += $$KF5_DIR/include/KF5/KI18n
DEPENDPATH += $$KF5_DIR/include/KF5/KI18n

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5SonnetUi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5SonnetUid
INCLUDEPATH += $$KF5_DIR/include/KF5/SonnetUi
DEPENDPATH += $$KF5_DIR/include/KF5/SonnetUi

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5XmlGui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5XmlGuid
INCLUDEPATH += $$KF5_DIR/include/KF5/KXmlGui
DEPENDPATH += $$KF5_DIR/include/KF5/KXmlGui

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5TextWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5TextWidgetsd
INCLUDEPATH += $$KF5_DIR/include/KF5/KTextWidgets
DEPENDPATH += $$KF5_DIR/include/KF5/KTextWidgets

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5ConfigWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5ConfigWidgetsd
INCLUDEPATH += $$KF5_DIR/include/KF5/KConfigWidgets
DEPENDPATH += $$KF5_DIR/include/KF5/KConfigWidgets

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5ConfigGui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5ConfigGuid
INCLUDEPATH += $$KF5_DIR/include/KF5/KConfigGui
DEPENDPATH += $$KF5_DIR/include/KF5/KConfigGui

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5WidgetsAddons
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5WidgetsAddonsd
INCLUDEPATH += $$KF5_DIR/include/KF5/KWidgetsAddons
DEPENDPATH += $$KF5_DIR/include/KF5/KWidgetsAddons

win32:CONFIG(release, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5TextEditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$KF5_DIR/lib/ -lKF5TextEditord
INCLUDEPATH += $$KF5_DIR/include/KF5/KTextEditor
DEPENDPATH += $$KF5_DIR/include/KF5/KTextEditor
