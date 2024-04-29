#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <weatherstationconfig.h>
#include "jsonparser.h"
#include "weatherdata.h"

#include "databasemanager.h"
#include <QLibrary>
typedef QJsonObject (*ApiToDataToJSON)(QJsonObject const &);

class ClientHTTP : public QObject
{
    Q_OBJECT
private :
    // QString apiKey="d4e153e384104917a01162245240801";//WeatherAPI
    // QString apiKey="6d953011087ba1a4bc7ae7a76159df2a";//OpenWeatherAPI
    // const QStringList citiesList=QStringList({"London", "Paris", "Berlin", "Osaka", "Beijing", "Toronto", "Chicago", "Abidjan", "Tunis" "Jerusalem", "Johannesbourg"});
    QStringList requestList;
    QString apiKey = WeatherStationConfig::getApikey();
    QLibrary library=QLibrary(WeatherStationConfig::getDllpath());
    ApiToDataToJSON apiToDataToJSON;
    // QTimer* timer;
public:
   explicit ClientHTTP( QObject *parent = nullptr);
    // QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;
    // void startRequest();
   void startRequestSerie();
   void getNextRequest();
   void startRequest(QString const &city);

   // QJsonObject apiToWeatherDatas(QJsonObject const &api_json);

   signals:
        void requestSerieEnd();
   private slots:
       void onfinish(QNetworkReply *rep);
   public slots:
       void requestWeatherDatas();

};
// extern QJsonObject apiToDataToJSON(QJsonObject  const &api_json);
#endif // CLIENTHTTP_H
