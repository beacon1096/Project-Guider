#include "BeaconAboutInterface.h"
#include "ui_BeaconAboutInterface.h"

BeaconAboutInterface::BeaconAboutInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BeaconAboutInterface)
{
    ui->setupUi(this);
    ui->titleLabel->setText(info.displayName);
    ui->versionLabel->setText(info.version);
    ui->LogoLabel->setPixmap(QPixmap(info.programLogo));

    info.buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " 0" ), "MMM dd yyyy");
    info.buildTime = QTime::fromString( __TIME__, "hh:mm:ss" );

    QString buildInfoText;
    buildInfoText.append(QString("%1 - %2<br>").arg(info.version).arg(info.buildType));
    buildInfoText.append(QString("%1%2%3<br>").arg(tr("Build date")).arg(": ").arg(info.buildDate.toString()));
    buildInfoText.append(QString("%1%2%3<br>").arg(tr("Build time")).arg(": ").arg(info.buildTime.toString()));

    ui->aboutBrowser->append(info.shortDescription);
    ui->aboutBrowser->append("");
    //ui->aboutBrowser->append("<br>");
    ui->aboutBrowser->append(buildInfoText);
    ui->aboutBrowser->append("");
    //ui->aboutBrowser->append("<br>");
    ui->aboutBrowser->append(info.copyrightStatement);
    ui->aboutBrowser->append("");
    //ui->aboutBrowser->append("<br>");
    ui->aboutBrowser->append(QString("<a href=\"%1\">%1</a>").arg(info.homepage));
    ui->aboutBrowser->append(info.license);

    ui->librariesBrowser->append(QString("%1 <i>%2</i> %3").arg(libHeader).arg(tr("BeaconFramework")).arg(BeaconFrameworkInfo::version));
    ui->librariesBrowser->append(QString("%1 <i>%2</i> %3 (%4 %5)").arg(libHeader).arg("Qt").arg(QT_VERSION_STR).arg(tr("build against")).arg(QT_VERSION_STR));
    ui->librariesBrowser->append(QString("%1 %2 <i>%3</i> %4").arg(libHeader).arg(tr("The")).arg(BeaconPlatformInfo::windowingSystem).arg(tr("windowing system")));
    ui->librariesBrowser->append("");
    ui->librariesBrowser->append(tr("  %1:").arg(tr("Plugins")));
    for(auto it=mainInfo.plugins.begin();it!=mainInfo.plugins.end();it++){
        ui->librariesBrowser->append(QString("%1 %2 (%3)").arg(libHeader).arg(it->pluginName).arg(it->pluginVersion));
    }
}

BeaconAboutInterface::~BeaconAboutInterface()
{
    delete ui;
}
