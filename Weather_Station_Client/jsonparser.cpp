#include "jsonparser.h"

bool JSONParser::writeJson(QJsonObject json_obj, QString file_path)
{
    /*Write a Json File*/
    QJsonDocument doc(json_obj);
    QFile file(file_path);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        return true;
    }
    return false;
}

QJsonObject JSONParser::readJsonFile(QString file_path)
{
    /*Read a Json File and return a JSON Object*/
    QFile file(file_path);
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        return doc.object();
    }
    return QJsonObject();
}

QJsonObject JSONParser::readJsonString(QString jsonstr)
{
    /*Convert a String to Json Object*/
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonstr.toUtf8());
    return json_doc.object();
}

QJsonObject JSONParser::readJsonBytes(QByteArray jsonbytes)
{
    /*Convert a bytes Array to Json Object*/
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonbytes);
    return json_doc.object();
}


QStringList JSONParser::jsonArray2StringList(QJsonArray &json_array){
    QStringList cities = QStringList();
    for(auto val : json_array)
    {
        cities.push_back(val.toString());
    }
    return cities;
}
