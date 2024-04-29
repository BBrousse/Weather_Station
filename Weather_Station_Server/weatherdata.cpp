#include "weatherdata.h"

WeatherData::WeatherData(int _timeutc=0, QString _city="", QString _weather="", double _temp=0.0, double _fl_temp=0.0, double _pressure=0.0, double _humidity=0.0, double _wind_speed=0.0, double _wind_deg=0.0)
{
    timeutc=_timeutc;
    city=_city;
    weather=_weather;
    temp=_temp;
    fl_temp=_fl_temp;
    pressure=_pressure;
    humidity=_humidity;
    wind_speed=_wind_speed;
    wind_deg=_wind_deg;
};

WeatherData::WeatherData(QJsonObject json_obj){

    timeutc=json_obj["timeutc"].toInt();
    weather=json_obj["weather"].toString();
    city=json_obj["city"].toString();
    temp=json_obj["temp"].toDouble();
    fl_temp=json_obj["fl_temp"].toDouble();
    pressure=json_obj["pressure"].toDouble();
    humidity=json_obj["humidity"].toDouble();
    wind_speed=json_obj["wind_speed"].toDouble();
    wind_deg=json_obj["wind_deg"].toDouble();
}


QJsonObject WeatherData::toJson(){
    QJsonObject json_obj= QJsonObject();
    json_obj.insert("timeutc", timeutc);
    json_obj.insert("city", city);
    json_obj.insert("weather", weather);

    json_obj.insert("temp", temp);
    json_obj.insert("fl_temp", fl_temp);
    json_obj.insert("pressure", pressure);

    json_obj.insert("humidity", humidity);
    json_obj.insert("wind_speed", wind_speed);
    json_obj.insert("wind_deg", wind_deg);
    return json_obj;
}

QString WeatherData::toString(){
    return "city:"%city%", time:"%QString::number(timeutc)%", weather:"%weather%
           ", temp:"%QString::number(temp)%", fl_temp"%QString::number(fl_temp)%
           ", pressure:"%QString::number(pressure)%", humidity:"%QString::number(humidity)%
           ", wind_speed:"%QString::number(wind_speed)%", wind_deg:"%QString::number(wind_deg);
}

int WeatherData::getTimeutc() const
{
    return timeutc;
}

QString WeatherData::getCity() const
{
    return city;
}

QString WeatherData::getWeather() const
{
    return weather;
}

double WeatherData::getTemp() const
{
    return temp;
}

double WeatherData::getFl_temp() const
{
    return fl_temp;
}

double WeatherData::getPressure() const
{
    return pressure;
}

double WeatherData::getHumidity() const
{
    return humidity;
}

double WeatherData::getWind_speed() const
{
    return wind_speed;
}

double WeatherData::getWind_deg() const
{
    return wind_deg;
}
