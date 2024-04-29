#ifndef WEATHERSTATIONCONFIG_H
#define WEATHERSTATIONCONFIG_H
#include <QSettings>
#define SETTINGS_PATH "D:/Projects/QT/Weather_Station/weathearStationClient.ini"
class WeatherStationConfig
{
public:

    static int getPort();
    static void setPort(int newPort);

    static QString getServer();
    static void setServer(const QString &newServer);

    static QSettings getSettings();
    static void setSettings(const QSettings &newSettings);
private :
    WeatherStationConfig();
    static QSettings settings;
    static int port;
    static QString server;
};

#endif // WEATHERSTATIONCONFIG_H
