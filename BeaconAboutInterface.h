#ifndef BEACONABOUTINTERFACE_H
#define BEACONABOUTINTERFACE_H

#include <QMainWindow>
#include <QLabel>
#include <QTextBrowser>
#include "BeaconApplicationInfoOld.h"
#include "BeaconPlatformInfo.h"
#include "BeaconFrameworkInfo.h"

namespace Ui {
class BeaconAboutInterface;
}

class BeaconAboutInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit BeaconAboutInterface(QWidget *parent = nullptr);
    ~BeaconAboutInterface();
    BeaconApplicationInfoOld info;
    //About

    //Lib
    const char libHeader='>';
    //Authors
    QWidget *authorsWidget;
    QLabel *tip;
    //Thanks to
    QWidget *thanksWidget;

private:
    Ui::BeaconAboutInterface *ui;
};

#endif // BEACONABOUTINTERFACE_H
