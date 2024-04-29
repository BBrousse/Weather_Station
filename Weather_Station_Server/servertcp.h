#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
// #include ""
#include "clienthttp.h"
#include "weatherstationconfig.h"
#define TCP_FIELD_CMD "cmd"
#define TCP_FIELD_PARAMS "params"
#define TCP_FIELD_RESULT "results"

#define TCP_CMD_CONNECT "connect"
#define TCP_CMD_REQUEST "request"

#define TCP_PARAMS_TIME "time"
#define TCP_PARAMS_TIME_FROM "from"
#define TCP_PARAMS_TIME_TO "to"
#define TCP_PARAMS_CITIES "cities"
#define TIMER_TIMEOUT 600000//micro sec


class ServerTCP : public QObject
{
	Q_OBJECT
public:
    explicit ServerTCP(QObject *parent = nullptr);
    void sendCommand(QTcpSocket* sock, QString const &cmd, QJsonArray const &params );

private:

	QTcpServer *mServer;
    ClientHTTP *httpcli;
    QTimer * timer;

signals:

private slots:

	void clientConnected();

	void dataReceived();
	void socketDisconnected();
    void connectRecieved(QTcpSocket* sock);
    void requestRecieved(QTcpSocket* sock, QJsonObject& params);
};
#endif // SERVERTCP_H
