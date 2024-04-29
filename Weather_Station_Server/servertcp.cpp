#include "servertcp.h"

ServerTCP::ServerTCP(QObject *parent)
    : QObject{parent}
{
    /*create TCP Server*/
    mServer = new QTcpServer(this);
    /*create HTTP Client*/
    httpcli = new ClientHTTP(this);
    timer = new QTimer(this);

    qDebug() << "init Server events";
    connect(mServer,SIGNAL(newConnection()),this,SLOT(clientConnected()));
    qDebug() << "init Weather events";
    httpcli->requestWeatherDatas();
    connect(timer, SIGNAL(timeout()), httpcli, SLOT(requestWeatherDatas()));
    timer->start(WeatherStationConfig::getTimeout());//--> 5min < temps de refresh de OpenWeatherAPI -- conflits de clefs
    /*Start TCP Server*/
    bool b = mServer->listen(QHostAddress::Any,WeatherStationConfig::getPort());
    if (b==false){
        qDebug() << "probleme ouverture port";
    }
}

void ServerTCP::clientConnected()
{
    QTcpSocket* sock = mServer->nextPendingConnection();
    connect(sock,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(sock,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));

    sock->write("connected");
}
void ServerTCP::dataReceived()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    QByteArray b = sock->readAll();
    qDebug() << b;
    QJsonDocument doc = QJsonDocument::fromJson(b);
    if(!doc.isNull()){
        qDebug() << b;
        qDebug() << "json datas recieved";
        QJsonObject root = doc.object();
        if(root.find(TCP_FIELD_CMD) != root.end())
        {
            QString cmd = root[TCP_FIELD_CMD].toString();
            if(cmd == TCP_CMD_CONNECT){
                /*Recieved a connection demand*/
                connectRecieved(sock);
            }
            if(cmd == TCP_CMD_REQUEST)
            {
                /*Recieved a request for datas*/
                QJsonObject params = root[TCP_FIELD_PARAMS].toObject();
                requestRecieved(sock,params);
            }
        }
        else{
            qDebug() << "invalid frame";
        }
    }
}

void ServerTCP::connectRecieved(QTcpSocket* sock){
    qDebug() << "connect request";
    QJsonArray results = QJsonArray();
    results.append(true);
    sendCommand(sock,TCP_CMD_CONNECT,results);
}

void ServerTCP::requestRecieved(QTcpSocket* sock, QJsonObject& params){
    /*Parsing message*/
    //Get times parameters
    QJsonObject time = params[TCP_PARAMS_TIME].toObject();
    int from_date = time["from"].toInt();
    int to_date = time ["to"].toInt();

    //Get targeted cities
    QJsonArray cities_json = params["cities"].toArray();
    QStringList cities = QStringList();
    for(auto city: cities_json){
        cities.push_back(city.toString());
    }
    qDebug() << "request datas";

    QJsonArray results = DatabaseManager::requestDatas(cities, from_date, to_date);
    sendCommand(sock,TCP_CMD_REQUEST,results);
}

void ServerTCP::sendCommand(QTcpSocket* sock, QString const &cmd, QJsonArray const &results ){
    QJsonObject root = QJsonObject();
    root.insert(TCP_FIELD_CMD,cmd);
    root.insert(TCP_FIELD_RESULT,results);
    QJsonDocument doc(root);
    QByteArray b = doc.toJson(doc.Compact);
    qDebug() << b;
    sock->write(b);
}

void ServerTCP::socketDisconnected()
{
    QTcpSocket* sock = (QTcpSocket*)sender();
    sock->deleteLater();
}
