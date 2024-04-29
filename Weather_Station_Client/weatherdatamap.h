#ifndef WEATHERDATAMAP_H
#define WEATHERDATAMAP_H

#include <QObject>
#include "weatherdata.h"
class WeatherDataMap : public QObject
{
    Q_OBJECT
public:
    explicit WeatherDataMap(QObject *parent = nullptr);

    QMap<QString, QVector<WeatherData *> > getWeatherDatasMap();
    QVector<WeatherData *> getWeatherDatasList();
    float getMinTemp();
    float getMaxTemp();

    float getMinFl_temp();
    float getMaxFl_temp();

    float getMinPressure();
    float getMaxPressure();

    float getMinHumidity();
    float getMaxHumidity();

    float getMinWindSpeed();
    float getMaxWindSpeed();

    float getMinWindDeg();
    float getMaxWindDeg();

    QVector<WeatherData*>& operator[](QString const city);
    WeatherData*& operator[](int const index);
    QList<QString> cities();
    int count();

    void clear();
    // static float toCelcius(float temp);

    static qint64 toUTCMilliseconds(int time_sec);
    static double toCelsius(double temp);

private :
    QMap<QString,QVector<WeatherData*>> weatherDatasMap= QMap<QString,QVector<WeatherData*>>();
    QVector<WeatherData*> weatherDatasList = QVector<WeatherData*>();
public slots :
    void updateDatas(const QJsonArray &datas);

signals:
    void datasUpdated();
};
double operator ""_Cel(const long double temp);
#endif // WEATHERDATAMAP_H
