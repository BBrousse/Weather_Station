#include "apidatatojson.h"

QJsonObject apiToDataToJSON(QJsonObject  const &api_json){
    qDebug() << "Use API Function";
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
}
