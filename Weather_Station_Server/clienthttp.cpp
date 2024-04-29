#include "clienthttp.h"

ClientHTTP::ClientHTTP(QObject *parent)
    : QObject{parent}
{
    if(!library.load()){
        /*Use a this as fallback if could not load library*/
        qDebug() << "failed loading library";
        qDebug() << library.errorString();
        apiToDataToJSON=[](QJsonObject const & api_json) {
            qDebug() << "Use Default Function";
            QJsonObject root =QJsonObject();
            root.insert("timeutc",api_json["dt"].toInt());
            root.insert("city",api_json["name"].toString());
            root.insert("weather",api_json["weather"].toArray()[0].toObject()["main"].toString());

            QJsonObject maindatas= api_json["main"].toObject();
            root.insert("temp",maindatas["temp"].toDouble());
            root.insert("fl_temp",maindatas["feels_like"].toDouble());
            root.insert("pressure",maindatas["pressure"].toDouble());
            root.insert("humidity",maindatas["humidity"].toDouble());

            QJsonObject winddatas= api_json["wind"].toObject();
            root.insert("wind_speed",winddatas["speed"].toDouble());
            root.insert("wind_deg",winddatas["deg"].toDouble());

            return root;
        };
    }
    else{
        qDebug() << "library loaded";
        /*apiToDataToJSON member is set to have to load the function only once*/
        apiToDataToJSON = (ApiToDataToJSON) library.resolve("apiToDataToJSON");
        if((ApiToDataToJSON) library.resolve("apiToDataToJSON")==nullptr){
            qDebug() << "Failed to load funtion 1";
        }
        if(apiToDataToJSON==nullptr){
            qDebug() << "Failed to load funtion";
        }
        qDebug() << library.errorString();
    }
}


void ClientHTTP::startRequestSerie(){
    qDebug() << "numberCites: "%QString::number(WeatherStationConfig::getCitieslist().count());

    requestList=QStringList();
    for(QString city : WeatherStationConfig::getCitieslist()){
        requestList.push_back(city);
    }
    getNextRequest();
}

void ClientHTTP::getNextRequest(){
    if(!requestList.isEmpty()){
        qDebug() << "will start request";
        startRequest(requestList.takeFirst());
    }
    else{
        emit requestSerieEnd();
    }
}

void ClientHTTP::startRequest(QString const &city){

    QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
    connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));
    // QString tmp = "http://api.weatherapi.com/v1/current.json?key="%apiKey%"&q=London";
    QString tmp = "https://api.openweathermap.org/data/2.5/weather?appid="%apiKey%"&q="%city;
    qDebug() << tmp;
    mgr->get(QNetworkRequest(QUrl(tmp)));
    qDebug() << "request sent";
}



void ClientHTTP::onfinish(QNetworkReply *rep)
{
    QByteArray bts = rep->readAll();
    qDebug() << bts;
    QJsonObject json_obj = JSONParser::readJsonBytes(bts);
    if(json_obj["cod"].toInt()==200){
        qDebug() << "Using apiToDataToJSON";
        if(apiToDataToJSON==nullptr){
            qDebug() << "Failed setting apiToDataToJSON";
        }
        WeatherData wd = WeatherData(apiToDataToJSON(json_obj));
        qDebug() << wd.toString();
        if(DatabaseManager::insertWeatherData(wd)){
             qDebug() << "datas inserted";
         }
        else{
            qDebug() << "insertion failed";
        }
    }
    qDebug() << "end of request";
    getNextRequest();
}


void ClientHTTP::requestWeatherDatas(){
    startRequestSerie();
}
