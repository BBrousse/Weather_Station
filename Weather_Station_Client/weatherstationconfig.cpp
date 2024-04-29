#include "weatherstationconfig.h"

QSettings WeatherStationConfig::settings = QSettings(SETTINGS_PATH, QSettings::IniFormat);
QString WeatherStationConfig::server = "";
int WeatherStationConfig::port = 0;

WeatherStationConfig::WeatherStationConfig() {}

QString WeatherStationConfig::getServer()
{
    if(server.isEmpty()){
        server = settings.value("server").toString();
    }
    return server;
}

void WeatherStationConfig::setServer(const QString &newServer)
{
    server = newServer;
}

int WeatherStationConfig::getPort()
{
    if(port==0){
        port = settings.value("port").toInt();
    }
    return port;
}

void WeatherStationConfig::setPort(int newPort)
{
    port = newPort;
}
