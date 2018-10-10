#include "BeaconPluginInfo.h"

BeaconPluginInfo::BeaconPluginInfo(QObject *parent) : QObject(parent)
{

}
BeaconPluginInfo::BeaconPluginInfo(QString name,QString version){
    pluginName=name;
    pluginVersion=version;
}
BeaconPluginInfo::BeaconPluginInfo(QString name,int version){
    pluginName=name;
    pluginVersion=QString::number(version);
}
BeaconPluginInfo::BeaconPluginInfo(const BeaconPluginInfo &target){
    pluginName=target.pluginName;
    pluginVersion=target.pluginVersion;
}
void BeaconPluginInfo::operator=(const BeaconPluginInfo &target)const{

}
