QT       += KConfigCore KConfigGui KConfigWidgets
QT       += KTextEditor
QT       += KCoreAddons KXmlGui KI18n KTextWidgets SonnetCore SonnetUi

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
