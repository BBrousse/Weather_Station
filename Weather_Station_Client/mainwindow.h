#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QChart>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include "clienttcp.h"
#include "weatherdatamap.h"
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

enum ChartView {TEMP, FL_TEMP, PRESSURE, HUMIDITY, WIND_SPEED, WIND_DEGREE};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStringList header = QStringList({"Date","City","Weather","Temperature", "Feel Like Temperature", "Pressure", "Humidity", "Wind Speed", "Wind Degree"});
    Ui::MainWindow *ui;
    ClientTCP *tcpcli;
    QChart* charts;
    ChartView curview=TEMP;
    WeatherDataMap weatherDataMap=WeatherDataMap();
    // void updateTableDatas(QJsonArray &root);

    QStringList getCitiesList();
    void addTempSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy);
    void addFlTempSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy);
    void addPressureSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy);
    void addHumidySerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy);
    void addWindSpeedSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy);
    void addWindDegSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy);
    void connnectGUIEvents();
public slots:
    // void updateDatas(QJsonArray &json_datas);
    void updateCitiesParams();
    void updateStartDate(const QDateTime&);
    void updateEndDate(const QDateTime&);
    void updateTableDatas();
    void updateCharts();
    void selectChart(int i);
};
#endif // MAINWINDOW_H
