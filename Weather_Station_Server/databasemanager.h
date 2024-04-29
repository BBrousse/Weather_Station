#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "weatherdata.h"
class DatabaseManager
{
private :
    static QString dbtype;
    static QString dbname;
    static QString dbpath;
    static bool is_opened;
    static QSqlDatabase db;
    DatabaseManager();
public :
    static void initDatabase();
    static QString getDbtype();
    static void setDbtype(const QString &newDbtype);
    static QString getDbname();
    static void setDbname(const QString &newDbname);
    static QString getDbpath();
    static void setDbpath(const QString &newDbpath);
    static bool insertWeatherData(WeatherData const &wd);
    static QJsonArray requestDatas();
    static QJsonArray requestDatas(QStringList &cities, int from_date, int to_date);
    static int getIntField(QSqlQuery &query, QString field);
    static double getRealField(QSqlQuery &query, QString field);
    static QString getStrField(QSqlQuery &query, QString field);
    static int getIntField(QSqlQuery &query, int field);
    static double getRealField(QSqlQuery &query, int field);
    static QString getStrField(QSqlQuery &query, int field);


};

#endif // DATABASEMANAGER_H
