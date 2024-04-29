#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QJsonDocument>
#include <QStandardItemModel>
#include "weatherstationconfig.h"
#include "weatherdata.h"

#define TCP_FIELD_CMD "cmd"
#define TCP_FIELD_PARAMS "params"
#define TCP_FIELD_RESULT "results"

#define TCP_CMD_CONNECT "connect"
#define TCP_CMD_REQUEST "request"

#define TCP_PARAMS_TIME "time"
#define TCP_PARAMS_TIME_FROM "from"
#define TCP_PARAMS_TIME_TO "to"
#define TCP_PARAMS_CITIES "cities"

class ClientTCP : public QObject
{
    Q_OBJECT
public:
    explicit ClientTCP(QObject *parent = nullptr);
    // QMap<QString,QVector<WeatherData*>> weatherDatasMap= QMap<QString,QVector<WeatherData*>>();
    // QVector<WeatherData*> weatherDatasList = QVector<WeatherData*>();
    void JSONArrayToStdItem(QJsonArray &root);
    QStringList getToRequestCities() const;
    void setToRequestCities(const QStringList &newToRequestCities);

    int getStartDate() const;
    void setStartDate(int newStartDate);

    int getEndDate() const;
    void setEndDate(int newEndDate);


    // QMap<QString, QVector<WeatherData *> > getWeatherDatasMap() const;
    // void setWeatherDatasMap(const QMap<QString, QVector<WeatherData *> > &newWeatherDatasMap);

    // QVector<WeatherData *> getWeatherDatasList() const;
    // void setWeatherDatasList(const QVector<WeatherData *> &newWeatherDatasList);
    // void updateDatas(QJsonArray &datas);

    // float getMinTemp();
    // float getMaxTemp();

    // float getMinFl_temp();
    // float getMaxFl_temp();

    // float getMinPressure();
    // float getMaxPressure();

    // float getMinHumidity();
    // float getMaxHumidity();

    // float getMinWindSpeed();
    // float getMaxWindSpeed();

    // float getMinWindDeg();
    // float getMaxWindDeg();

private:
    QTcpSocket* mSocket;
    QStringList toRequestCities=QStringList();
    int startDate;
    int endDate;
private slots:
    void dataReceived();
    void socketConnected();
    void socketDisconnected();
    void sendRequest();
    void sendCommand(QString const &cmd, QJsonObject const &params );

// public slots:

signals:
    void datasUpdated();
    void resultsRecieved(const QJsonArray &results);
};

#endif // CLIENTTCP_H
