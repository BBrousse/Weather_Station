#include <QCoreApplication>
#include <QSqlDatabase>
#include <QTimer>
#include "servertcp.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // QSettings settings("D:/Projects/QT/Weather_Station/weathearStationServer.ini", QSettings::IniFormat);

    // settings.beginGroup("Cities");
    // settings.setValue ( "test", true );
    // QStringList citiesList=QStringList({"London", "Paris", "Berlin", "Osaka", "Beijing", "Toronto", "Chicago", "Abidjan", "Tunis" "Jerusalem", "Johannesbourg"});
    // settings.setValue("cities",citiesList);
    // settings.endGroup();
    ServerTCP s;

    return a.exec();
}
