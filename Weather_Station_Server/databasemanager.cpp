#include "databasemanager.h"

QString DatabaseManager::getDbtype()
{
    return dbtype;
}

void DatabaseManager::setDbtype(const QString &newDbtype)
{
    dbtype = newDbtype;
}

QString DatabaseManager::getDbname()
{
    return dbname;
}

void DatabaseManager::setDbname(const QString &newDbname)
{
    dbname = newDbname;
}

QString DatabaseManager::getDbpath()
{
    return dbpath;
}

void DatabaseManager::setDbpath(const QString &newDbpath)
{
    dbpath = newDbpath;
}

DatabaseManager::DatabaseManager() {}
QString DatabaseManager::dbtype = "QSQLITE";
QString DatabaseManager::dbname = "TestWeatherDB";
QString DatabaseManager::dbpath = "D:/Projects/DB/"%dbname%".db";
QSqlDatabase DatabaseManager::db = QSqlDatabase::addDatabase(dbtype,dbname);
bool DatabaseManager::is_opened = false;

void DatabaseManager::initDatabase(){
    // db = QSqlDatabase::addDatabase(dbtype,dbname);
    db.setDatabaseName(dbpath);
    is_opened=db.open();
}


bool DatabaseManager::insertWeatherData(WeatherData const &wd){
    //If database is not opened try to open it
    if(!is_opened){
        qDebug() << "database not opened, try open database";
        initDatabase();
    }
    if(is_opened){
        qDebug() << "database opened, try insert datas";
        QSqlQuery query = QSqlQuery(db);
        // int timeutc;//->dt
        // QString city;//->name
        // QString weather; //->weather -> main
        // double temp; //->main -> temp (Kelvin)
        // double fl_temp;//->main -> feels_like (Kelvin)
        // double pressure;//->main -> pressure
        // double humidity;//->main -> humidity
        // double wind_speed;//->wind->speed
        // double wind_deg;//->wind->deg
        QString listfields= "timeutc, city, weather, temp, fl_temp, pressure, humidity, wind_speed, wind_deg";
        QString querystr =QString("INSERT INTO WeatherDatas ("%listfields%") VALUES (%1, '%2', '%3', %4, %5, %6, %7, %8 , %9);").arg(
            wd.getTimeutc()).arg(
            wd.getCity()).arg(
            wd.getWeather()).arg(
            wd.getTemp()).arg(
            wd.getFl_temp()).arg(
            wd.getPressure()).arg(
            wd.getHumidity()).arg(
            wd.getWind_speed()).arg(
            wd.getWind_deg());
        qDebug() << "Query is : " << querystr;
        bool ret = query.exec(querystr);
        if(!ret){
            QSqlError err = query.lastError();
            qDebug() << err;
        }
        return ret;
    }
    qDebug() << "failed opening database";
    //If database still not opened leave -> request failed
    return false;
}

int DatabaseManager::getIntField(QSqlQuery &query, QString field){
    return query.value(field).toInt();
}
int DatabaseManager::getIntField(QSqlQuery &query, int field){
    return query.value(field).toInt();
}

double DatabaseManager::getRealField(QSqlQuery &query, QString field){
    return query.value(field).toDouble();
}
double DatabaseManager::getRealField(QSqlQuery &query, int field){
    return query.value(field).toDouble();
}

QString DatabaseManager::getStrField(QSqlQuery &query, QString field){
    return query.value(field).toString();
}
QString DatabaseManager::getStrField(QSqlQuery &query, int field){
    return query.value(field).toString();
}

QJsonArray DatabaseManager::requestDatas(){
    QJsonArray root;
    if(!is_opened){
        qDebug() << "database not opened, try open database";
        initDatabase();
    }
    if(is_opened){
        QSqlQuery query = QSqlQuery(db);
        QString querystr = "SELECT timeutc, city, weather, temp, fl_temp, pressure, humidity, wind_speed, wind_deg FROM WeatherDatas LIMIT 10;";
        bool ret = query.exec(querystr);
        if(!ret){
            QSqlError err = query.lastError();
            qDebug() << err;
        }
        while (query.next()) {
            QJsonObject tmp;
            // QVector<QString> result;
            int timeutc=getIntField(query,"timeutc");

            QString city=getStrField(query,"city");
            QString weather=getStrField(query,"weather");

            double temp=getRealField(query,"temp");
            double fl_temp=getRealField(query,"fl_temp");
            double pressure=getRealField(query,"pressure");
            double humidity=getRealField(query,"humidity");
            double wind_speed=getRealField(query,"wind_speed");
            double wind_deg=getRealField(query,"wind_deg");
            tmp.insert("timeutc", timeutc);
            tmp.insert("city",city);
            tmp.insert("weather",weather);
            tmp.insert("temp",temp);
            tmp.insert("fl_temp",fl_temp);
            tmp.insert("pressure",pressure);
            tmp.insert("humidity",humidity);
            tmp.insert("wind_speed",wind_speed);
            tmp.insert("wind_deg",wind_deg);
            root.push_back(tmp);
        }
    }
    return root;
}

QString buildCitiesCondition(QStringList &cities){
    if(cities.count()==0){
        return "";
    }
    QString cnd="city='"%cities[0]%"'";
    for(int i =1; i < cities.count(); i ++){
        cnd+=" OR city='"%cities[i]%"'";
    }
    return cnd;
}

QString buildTimeCondition(int from_date, int to_date){
    // QString cnd="";
    if(from_date >-1 && to_date>-1){
        return "timeutc >="%QString::number(from_date)%" AND "%"timeutc <="%QString::number(to_date);
    }
    if(from_date > -1){
        return "timeutc >="%QString::number(from_date);
    }
    if(to_date > -1){
        return "timeutc <="%QString::number(to_date);
    }
    return "";
}

QString buildRequest(QStringList &cities, int from_date, int to_date){
    QString fields = "timeutc, city, weather, temp, fl_temp, pressure, humidity, wind_speed, wind_deg";
    QString cnd_cities = buildCitiesCondition(cities);
    QString cnd_time = buildTimeCondition(from_date,to_date);
    if(cnd_cities.isEmpty() && cnd_time.isEmpty()){
        return "SELECT "%fields%" FROM WeatherDatas;";
    }
    if(cnd_cities.isEmpty()){
        return "SELECT "%fields%" FROM WeatherDatas WHERE "%cnd_time%";";
    }
    if(cnd_time.isEmpty()){
        return "SELECT "%fields%" FROM WeatherDatas WHERE "%cnd_cities%";";
    }
    return "SELECT "%fields%" FROM WeatherDatas WHERE ("%cnd_cities%") AND ("%cnd_time%");";
}

QJsonArray DatabaseManager::requestDatas(QStringList &cities, int from_date, int to_date){
    QJsonArray root;
    if(!is_opened){
        qDebug() << "database not opened, try open database";
        initDatabase();
    }
    if(is_opened){
        QSqlQuery query = QSqlQuery(db);
        QString querystr =buildRequest(cities, from_date, to_date);
        qDebug() << querystr;
        bool ret = query.exec(querystr);
        if(!ret){
            QSqlError err = query.lastError();
            qDebug() << err;
        }
        while (query.next()) {
            QJsonObject tmp;
            // QVector<QString> result;
            int timeutc=getIntField(query,"timeutc");

            QString city=getStrField(query,"city");
            QString weather=getStrField(query,"weather");

            double temp=getRealField(query,"temp");
            double fl_temp=getRealField(query,"fl_temp");
            double pressure=getRealField(query,"pressure");
            double humidity=getRealField(query,"humidity");
            double wind_speed=getRealField(query,"wind_speed");
            double wind_deg=getRealField(query,"wind_deg");
            tmp.insert("timeutc", timeutc);
            tmp.insert("city",city);
            tmp.insert("weather",weather);
            tmp.insert("temp",temp);
            tmp.insert("fl_temp",fl_temp);
            tmp.insert("pressure",pressure);
            tmp.insert("humidity",humidity);
            tmp.insert("wind_speed",wind_speed);
            tmp.insert("wind_deg",wind_deg);
            root.push_back(tmp);
        }
    }
    return root;
}
