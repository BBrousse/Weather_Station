#include "clienttcp.h"
#include "qjsonarray.h"
#include "qjsonobject.h"

ClientTCP::ClientTCP(QObject *parent):
    QObject{parent}
{
    mSocket = new QTcpSocket(this);

    connect(mSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(mSocket,SIGNAL(connected()),this,SLOT(socketConnected()));
    connect(mSocket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
    mSocket->connectToHost(WeatherStationConfig::getServer(),WeatherStationConfig::getPort());
}

QStringList ClientTCP::getToRequestCities() const
{
    return toRequestCities;
}

void ClientTCP::setToRequestCities(const QStringList &newToRequestCities)
{
    toRequestCities = newToRequestCities;
}

int ClientTCP::getStartDate() const
{
    return startDate;
}

void ClientTCP::setStartDate(int newStartDate)
{
    startDate = newStartDate;
}

int ClientTCP::getEndDate() const
{
    return endDate;
}

void ClientTCP::setEndDate(int newEndDate)
{
    endDate = newEndDate;
}


void ClientTCP::dataReceived()
{
    QByteArray b = mSocket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(b);
    if(!doc.isNull()){
        QJsonDocument doc= QJsonDocument::fromJson(b);
        QJsonObject root = doc.object();
        if(root.find(TCP_FIELD_CMD) != root.end())
        {
            QString cmd = root[TCP_FIELD_CMD].toString();
            if(cmd == TCP_CMD_CONNECT){
                qDebug()  << "connected" ;
            }
            if(cmd == TCP_CMD_REQUEST)
            {
                QJsonArray results = root[TCP_FIELD_RESULT].toArray();
                emit resultsRecieved(results);
            }

        }
    }
}

void ClientTCP::socketConnected()
{

    sendCommand(TCP_CMD_CONNECT,QJsonObject());
}

void ClientTCP::socketDisconnected()
{
    qDebug() << "disconnected";
}

void ClientTCP::sendRequest(){
    QJsonObject params=QJsonObject();

    QJsonObject time_json=QJsonObject();
    time_json.insert(TCP_PARAMS_TIME_FROM,startDate);
    time_json.insert(TCP_PARAMS_TIME_TO,endDate);
    params.insert(TCP_PARAMS_TIME,time_json);
    params.insert(TCP_PARAMS_CITIES,QJsonArray::fromStringList(toRequestCities));

    sendCommand(TCP_CMD_REQUEST, params);
}

void ClientTCP::sendCommand(QString const &cmd, QJsonObject const &params ){
    QJsonObject root = QJsonObject();
    root.insert(TCP_FIELD_CMD,cmd);
    if(params.isEmpty()){
        root.insert(TCP_FIELD_PARAMS,QJsonValue::Null);
    }
    root.insert(TCP_FIELD_PARAMS,params);
    QJsonDocument doc(root);
    mSocket->write(doc.toJson(doc.Compact));
}
