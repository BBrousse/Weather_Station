#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
class  JSONParser
{
public:
    JSONParser(){};
    static QJsonObject readJsonFile(QString file_path);
    static bool writeJson(QJsonObject json_obj, QString file_path);
    static QJsonObject readJsonString(QString jsonstr);
    static QJsonObject readJsonBytes(QByteArray jsonbytes);
    static QStringList jsonArray2StringList(QJsonArray &json_array);
};

#endif // JSONPARSER_H
