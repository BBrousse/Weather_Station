#ifndef WEATHERSTATIONCONFIG_H
#define WEATHERSTATIONCONFIG_H
#include <QSettings>
#define SETTINGS_PATH "D:/Projects/QT/Weather_Station/weathearStationServer.ini"

class WeatherStationConfig
{
public:

    static int getPort();

    static QStringList getCitieslist();

    static QString getDb_type();
    static QString getDb_name();
    static QString getDb_basepath();
    static QString getDb_ext();

    static int getTimeout();

    static QString getDllpath();

    static QString getApikey();

private :
    WeatherStationConfig();
    static QStringList citieslist;
    static QSettings settings;
    static int port;
    static int timeout;
    static QString db_type;
    static QString db_name;
    static QString db_basepath;
    static QString db_ext;
    static QString dllpath;
    static QString apikey;
};

#endif // WEATHERSTATIONCONFIG_H
