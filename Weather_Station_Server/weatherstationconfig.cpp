#include "weatherstationconfig.h"
QSettings WeatherStationConfig::settings = QSettings(SETTINGS_PATH, QSettings::IniFormat);
QStringList WeatherStationConfig::citieslist = QStringList();

int WeatherStationConfig::port=0;
QString WeatherStationConfig::db_type="";
QString WeatherStationConfig::db_name="";
QString WeatherStationConfig::db_basepath="";
QString WeatherStationConfig::db_ext="";
int WeatherStationConfig::timeout=0;
QString WeatherStationConfig::dllpath="";
QString WeatherStationConfig::apikey="";
WeatherStationConfig::WeatherStationConfig() {}

QString WeatherStationConfig::getApikey()
{
    if(apikey.isEmpty()){
        apikey=settings.value("apikey").toString();
    }
    return apikey;
}

QString WeatherStationConfig::getDllpath()
{
    if(dllpath.isEmpty()){
        dllpath=settings.value("dllpath").toString();
    }
    return dllpath;
}

QString WeatherStationConfig::getDb_type()
{
    if(db_type.isEmpty()){
        db_type=settings.value("Database/type").toString();
    }
    return db_type;
}

QString WeatherStationConfig::getDb_name()
{
    if(db_name.isEmpty()){
        db_name=settings.value("Database/name").toString();
    }
    return db_name;
}

QString WeatherStationConfig::getDb_basepath()
{
    if(db_basepath.isEmpty()){
        db_basepath=settings.value("Database/basepath").toString();
    }
    return db_basepath;
}

QString WeatherStationConfig::getDb_ext()
{
    if(db_ext.isEmpty()){
        db_ext=settings.value("Database/ext").toString();
    }
    return db_ext;
}

int WeatherStationConfig::getPort()
{
    if(port==0){
        port=settings.value("port").toInt();
    }
    return port;
}

QStringList WeatherStationConfig::getCitieslist()
{
    if(citieslist.isEmpty()){
        citieslist.append( settings.value("Cities/cities").toStringList());
    }
    return citieslist;
}

int WeatherStationConfig::getTimeout()
{
    if(timeout == 0){
        timeout=settings.value("timeout").toInt()*1000;
    }
    return timeout;
}
