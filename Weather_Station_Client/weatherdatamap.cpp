#include "weatherdatamap.h"

WeatherDataMap::WeatherDataMap(QObject *parent)
    : QObject{parent}
{}

QMap<QString, QVector<WeatherData *>> WeatherDataMap::getWeatherDatasMap()
{
    return weatherDatasMap;
}

QVector<WeatherData *> WeatherDataMap::getWeatherDatasList()
{
    return weatherDatasList;
}

void updateDatas(QJsonArray &datas);

float WeatherDataMap::getMaxTemp(){

    float max = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getTemp();
        if(tmp > max){
            max = tmp;
        }
    }
    return max;
}

float WeatherDataMap::getMinTemp(){

    float min = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getTemp();
        if(min == 0 || tmp < min){
            min = tmp;
        }
    }
    return min;
}

float WeatherDataMap::getMinFl_temp(){

    float min = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getFl_temp();
        if(min == 0 || tmp < min){
            min = tmp;
        }
    }
    return min;
}

float WeatherDataMap::getMaxFl_temp(){

    float max = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getFl_temp();
        if(tmp > max){
            max = tmp;
        }
    }
    return max;
}

float WeatherDataMap::getMinPressure(){

    float min = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getPressure();
        if(min == 0 || tmp < min){
            min = tmp;
        }
    }
    return min;
}

float WeatherDataMap::getMaxPressure(){

    float max = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getPressure();
        if(tmp > max){
            max = tmp;
        }
    }
    return max;
}

float WeatherDataMap::getMinHumidity(){

    float min = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getHumidity();
        if(min == 0 || tmp < min){
            min = tmp;
        }
    }
    return min;
}

float WeatherDataMap::getMaxHumidity(){

    float max = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getHumidity();
        if(tmp > max){
            max = tmp;
        }
    }
    return max;
}

float WeatherDataMap::getMinWindSpeed(){

    float min = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getWind_speed();
        if(min == 0 || tmp < min){
            min = tmp;
        }
    }
    return min;
}

float WeatherDataMap::getMaxWindSpeed(){

    float max = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getWind_speed();
        if(tmp > max){
            max = tmp;
        }
    }
    return max;
}

float WeatherDataMap::getMinWindDeg(){

    float min = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getWind_deg();
        if(min == 0 || tmp < min){
            min = tmp;
        }
    }
    return min;
}

float WeatherDataMap::getMaxWindDeg(){

    float max = 0;
    for(int i=0; i < weatherDatasList.count(); i++){
        float tmp = weatherDatasList[i]->getWind_deg();
        if(tmp > max){
            max = tmp;
        }
    }
    return max;
}
double operator ""_Cel(const long double  temp){
    return temp - 273.5;
}


QVector<WeatherData*>& WeatherDataMap::operator[](QString const city){
    return weatherDatasMap[city];
}

WeatherData*& WeatherDataMap::operator[](int const index){
    return weatherDatasList[index];
}

void WeatherDataMap::clear(){
    weatherDatasMap.clear();
    weatherDatasList.clear();
}

void WeatherDataMap::updateDatas(QJsonArray const &datas){
    clear();
    for(auto json_obj : datas){
        QJsonObject elt = json_obj.toObject();
        WeatherData* data = new WeatherData(elt);
        QString city = data->getCity();
        if(weatherDatasMap.find(city)==weatherDatasMap.end()){
            weatherDatasMap.insert(city,QVector<WeatherData*>());
        }
        weatherDatasMap[city].push_back(data);
        weatherDatasList.push_back(data);
    }
    emit datasUpdated();
}

QList<QString> WeatherDataMap::cities(){
    return weatherDatasMap.keys();
}

int WeatherDataMap::count(){
    return weatherDatasList.count();
}

qint64 WeatherDataMap::toUTCMilliseconds(int time_sec){
    return QDateTime::fromSecsSinceEpoch(time_sec).toMSecsSinceEpoch();
}

double WeatherDataMap::toCelsius(double temp){
    return temp - 273.15;
}
