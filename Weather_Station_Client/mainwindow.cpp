#include "mainwindow.h"
#include "qobjectdefs.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    tcpcli = new ClientTCP(this);
    ui->setupUi(this);
    charts = new QChart();

    charts->setTitle("Temp of cities");
    charts->setTheme(QChart::ChartThemeLight);
    ui->weather_charts->setChart(charts);


    ui->datas_table_w->setColumnCount(header.count());
    ui->datas_table_w->setHorizontalHeaderLabels(header);

    QStringList citiesList = getCitiesList();
    ui->cities_list->addItems(citiesList);
    ui->cities_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

    ui->datas_table_w->show();

    connnectGUIEvents();
    ui->cities_list->selectAll();
    ui->from_datetime->setDateTime(QDateTime::currentDateTime());
    ui->to_datetime->setDateTime(QDateTime::currentDateTime());
}

void MainWindow::connnectGUIEvents(){
    /*To send request to the server when pressing request button*/
    connect(ui->request_btn,SIGNAL(pressed()),tcpcli,SLOT(sendRequest()));

    /*To change list of selected cities when selecting them in the list widget*/
    connect(ui->cities_list,SIGNAL(itemSelectionChanged()),this,SLOT(updateCitiesParams()));

    /*To update the interval datas when changing value on the DateTime fields*/
    connect(ui->from_datetime,SIGNAL(dateTimeChanged(const QDateTime &)),this,SLOT(updateStartDate(const QDateTime &)));
    connect(ui->to_datetime,SIGNAL(dateTimeChanged(const QDateTime &)),this,SLOT(updateEndDate(const QDateTime &)));

    /*To put datas in the WeatherDatasMap when recieving result*/
    connect(tcpcli,SIGNAL(resultsRecieved(const QJsonArray &)),&weatherDataMap,SLOT(updateDatas(const QJsonArray &)));

    /*To udpate the displays when WeatherDatasMap is updated*/
    connect(&weatherDataMap,SIGNAL(datasUpdated()),this,SLOT(updateTableDatas()));
    connect(&weatherDataMap,SIGNAL(datasUpdated()),this,SLOT(updateCharts()));

    /*To changed displayed chart when selecting a new field in combo box*/
    connect(ui->chartselect_cb,SIGNAL(currentIndexChanged(int)),this, SLOT(selectChart(int)));
}

QStringList MainWindow::getCitiesList(){
    //Do a database request instead
   return QStringList({"London", "Paris", "Berlin", "Osaka", "Beijing", "Toronto", "Chicago", "Abidjan", "Tunis", "Jerusalem", "Johannesbourg"});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTableDatas(){
    ui->datas_table_w->clearContents();
    ui->datas_table_w->setRowCount(0);
    for(auto data : weatherDataMap.getWeatherDatasList()){
        int cur_row=ui->datas_table_w->rowCount();
        ui->datas_table_w->setRowCount(cur_row+1);

        ui->datas_table_w->setItem(cur_row,0,new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(data->getTimeutc()).toLocalTime().toString()));
        ui->datas_table_w->setItem(cur_row,1,new QTableWidgetItem(data->getCity()));
        ui->datas_table_w->setItem(cur_row,2,new QTableWidgetItem(data->getWeather()));

        ui->datas_table_w->setItem(cur_row,3,new QTableWidgetItem(QString::number(data->getTemp()-273.15)));
        ui->datas_table_w->setItem(cur_row,4,new QTableWidgetItem(QString::number(data->getFl_temp()-273.15)));
        ui->datas_table_w->setItem(cur_row,5,new QTableWidgetItem(QString::number(data->getPressure())));

        ui->datas_table_w->setItem(cur_row,6,new QTableWidgetItem(QString::number(data->getHumidity())));
        ui->datas_table_w->setItem(cur_row,7,new QTableWidgetItem(QString::number(data->getWind_speed())));
        ui->datas_table_w->setItem(cur_row,8,new QTableWidgetItem(QString::number(data->getWind_deg())));
    }
    ui->datas_table_w->show();
}

void MainWindow::selectChart(int i){
    curview=ChartView(i);
    updateCharts();
}

void MainWindow::updateCharts(){
    /*Reseting axes*/
    for(auto serie : charts->series())
    {
        for(auto axis : charts->axes(Qt::Horizontal, serie))
        {
            charts->removeAxis(axis);
        }
        for(auto axis : charts->axes(Qt::Vertical, serie))
        {
            charts->removeAxis(axis);
        }
    }

    /*Reseting seris*/
    charts->removeAllSeries();


    if(weatherDataMap.count() > 0){
        /*Check if map got datas it may cause issues when creating axes on attach to empty series*/
        auto axisX = new QDateTimeAxis;
        axisX->setTickCount(5);
        axisX->setFormat("dd-MM-yyyy h:mm");
        axisX->setTitleText("Date");
        axisX->setMin(QDateTime::fromSecsSinceEpoch(tcpcli->getStartDate()));
        axisX->setMax(QDateTime::fromSecsSinceEpoch(tcpcli->getEndDate()));
        charts->addAxis(axisX, Qt::AlignBottom);

        auto axisY = new QValueAxis;


        charts->addAxis(axisY, Qt::AlignLeft);

        for(QString city :  weatherDataMap.cities()){
            switch (curview) {
            case TEMP:
                charts->setTitle("Temperature");
                axisY->setTitleText("Temperature");
                axisY->setLabelFormat("%i C");
                axisY->setMin(WeatherDataMap::toCelsius(weatherDataMap.getMinTemp()));
                axisY->setMax(WeatherDataMap::toCelsius(weatherDataMap.getMaxTemp()));
                addTempSerie(city, axisX, axisY);
                break;

            case FL_TEMP:
                charts->setTitle("Feel Like Temperature");
                axisY->setTitleText("Feel Like Temperature");
                axisY->setLabelFormat("%i C");
                axisY->setMin(WeatherDataMap::toCelsius(weatherDataMap.getMinFl_temp()));
                axisY->setMax(WeatherDataMap::toCelsius(weatherDataMap.getMaxFl_temp()));
                addFlTempSerie(city, axisX, axisY);
                break;

            case PRESSURE:
                charts->setTitle("Pressure");
                axisY->setTitleText("Pressure");
                axisY->setLabelFormat("%i hPa");
                axisY->setMin(weatherDataMap.getMinPressure());
                axisY->setMax(weatherDataMap.getMaxPressure());
                addPressureSerie(city, axisX, axisY);
                break;

            case HUMIDITY:
                charts->setTitle("Humidity");
                axisY->setTitleText("Humidity");
                axisY->setLabelFormat("%i%");
                axisY->setMin(weatherDataMap.getMinHumidity());
                axisY->setMax(weatherDataMap.getMaxHumidity());
                addHumidySerie(city, axisX, axisY);
                break;

            case WIND_SPEED:
                charts->setTitle("Wind Speed");
                axisY->setTitleText("Wind Speed");
                axisY->setLabelFormat("%i m/s");
                axisY->setMin(weatherDataMap.getMinWindSpeed());
                axisY->setMax(weatherDataMap.getMaxWindSpeed());
                addWindSpeedSerie(city, axisX, axisY);
                break;

            case WIND_DEGREE:
                charts->setTitle("Wind Degree");
                axisY->setTitleText("Wind Degree");
                axisY->setLabelFormat("%i");
                axisY->setMin(weatherDataMap.getMinWindDeg());
                axisY->setMax(weatherDataMap.getMaxWindDeg());
                addWindDegSerie(city, axisX, axisY);
                break;

            default:
                break;
            }
        }
    }
}

void MainWindow::addTempSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy){
    QLineSeries *serie = new QLineSeries();

    for(auto wd :weatherDataMap[city])
    {
        /*Convert from Kelvin to Celcius*/
        serie->append(WeatherDataMap::toUTCMilliseconds(wd->getTimeutc()),WeatherDataMap::toCelsius(wd->getTemp()));
    }

    serie->setName(city);
    charts->addSeries(serie);
    serie->attachAxis(axisx);
    serie->attachAxis(axisy);

}

void MainWindow::addFlTempSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy){
    QLineSeries *serie = new QLineSeries();

    for(auto wd : weatherDataMap[city])
    {
        /*Convert from Kelvin to Celcius*/
        serie->append(WeatherDataMap::toUTCMilliseconds(wd->getTimeutc()),WeatherDataMap::toCelsius(wd->getFl_temp()));
    }

    serie->setName(city);
    charts->addSeries(serie);
    serie->attachAxis(axisx);
    serie->attachAxis(axisy);

}

void MainWindow::addPressureSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy){
    QLineSeries *serie = new QLineSeries();

    for(auto wd : weatherDataMap[city])
    {
        serie->append(WeatherDataMap::toUTCMilliseconds(wd->getTimeutc()),wd->getPressure());
    }
    serie->setName(city);
    charts->addSeries(serie);
    serie->attachAxis(axisx);
    serie->attachAxis(axisy);

}

void MainWindow::addHumidySerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy){
    QLineSeries *serie = new QLineSeries();

    for(auto wd : weatherDataMap[city])
    {
        serie->append(WeatherDataMap::toUTCMilliseconds(wd->getTimeutc()),wd->getHumidity());
    }
    serie->setName(city);
    charts->addSeries(serie);
    serie->attachAxis(axisx);
    serie->attachAxis(axisy);
}

void MainWindow::addWindSpeedSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy){
    QLineSeries *serie = new QLineSeries();

    for(auto wd : weatherDataMap[city])
    {
        serie->append(WeatherDataMap::toUTCMilliseconds(wd->getTimeutc()),wd->getWind_speed());
    }
    serie->setName(city);
    charts->addSeries(serie);
    serie->attachAxis(axisx);
    serie->attachAxis(axisy);
}

void MainWindow::addWindDegSerie(QString city, QDateTimeAxis* axisx, QValueAxis* axisy){
    QLineSeries *serie = new QLineSeries();

    for(auto wd : weatherDataMap[city])
    {
        serie->append(WeatherDataMap::toUTCMilliseconds(wd->getTimeutc()),wd->getWind_deg());
    }
    serie->setName(city);
    charts->addSeries(serie);
    serie->attachAxis(axisx);
    serie->attachAxis(axisy);
}

void MainWindow::updateCitiesParams(){
    QStringList cities = QStringList();
    auto listItem = ui->cities_list->selectedItems();
    for(auto item : listItem){
        cities.push_back(item->text());
    }
    tcpcli->setToRequestCities(cities);
}

void MainWindow::updateStartDate(const QDateTime& datetime){
    int timeUtc = datetime.toUTC().toSecsSinceEpoch();
    tcpcli->setStartDate(timeUtc);
    qDebug() << tcpcli->getStartDate();
}

void MainWindow::updateEndDate(const QDateTime& datetime){
    int timeUtc = datetime.toUTC().toSecsSinceEpoch();
    tcpcli->setEndDate(timeUtc);
    qDebug() << tcpcli->getEndDate();
}
