#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class  WeatherData
{
private :
    int timeutc;//->dt
    QString city;//->name
    QString weather; //->weather -> main
    double temp; //->main -> temp (Kelvin)
    double fl_temp;//->main -> feels_like (Kelvin)
    double pressure;//->main -> pressure
    double humidity;//->main -> humidity
    double wind_speed;//->wind->speed
    double wind_deg;//->wind->deg

public:
    WeatherData(QJsonObject json_obj);
    WeatherData(int _timeutc, QString _city, QString _weather, double _temp, double _fl_temp, double _pressure, double _humidity, double _wind_speed, double _wind_deg);
    QString toString();
    int getTimeutc() const;
    QString getCity() const;
    QString getWeather() const;
    double getTemp() const;
    double getFl_temp() const;
    double getPressure() const;
    double getHumidity() const;
    double getWind_speed() const;
    double getWind_deg() const;
    QJsonObject toJson();


};




#endif // WEATHERDATA_H
