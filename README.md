# Weather Station <!-- omit in toc -->

## Content Table <!-- omit in toc -->

- [1. Description](#1-description)
	- [1.1. Current State](#11-current-state)
		- [1.1.1. Client HTTP/Server](#111-client-httpserver)
	- [1.2. Current Goal](#12-current-goal)
		- [1.2.1. Improvements](#121-improvements)
- [2. Sub-projects](#2-sub-projects)
	- [2.1. Weather\_Station\_Client](#21-weather_station_client)
		- [2.1.1. Weather\_Station\_Client Classes](#211-weather_station_client-classes)
	- [2.2. Weather\_Station\_Server](#22-weather_station_server)
		- [2.2.1. Weather\_Station\_Server Classes](#221-weather_station_server-classes)
	- [2.3. ApiDataToJson](#23-apidatatojson)
- [3. Protocol](#3-protocol)
	- [3.1. Client Data Frame](#31-client-data-frame)
	- [3.2. Server Data Frame](#32-server-data-frame)
		- [3.2.1. Connection Data Frame](#321-connection-data-frame)
		- [3.2.2. request Data Frame](#322-request-data-frame)
- [4. Configuration](#4-configuration)
	- [4.1. Settings](#41-settings)
		- [4.1.1. HTTP Client](#411-http-client)
		- [4.1.2. TCP Server](#412-tcp-server)
		- [4.1.3. TCP Client](#413-tcp-client)
- [5. Troubleshooting](#5-troubleshooting)
- [6. To Do](#6-to-do)
	- [6.1. TCP Client/Server](#61-tcp-clientserver)
		- [6.1.1. TCP Client](#611-tcp-client)
		- [6.1.2. HTTP Client](#612-http-client)
		- [6.1.3. Configuration file](#613-configuration-file)
		- [6.1.4. IHM](#614-ihm)
		- [6.1.5. Documentation](#615-documentation)
		- [6.1.6. TCP Protocol](#616-tcp-protocol)
- [7. See Also](#7-see-also)
	- [7.1. Weather APIs](#71-weather-apis)
		- [7.1.1. OpenWeatherAPI](#711-openweatherapi)
		- [7.1.2. WeatherAPI](#712-weatherapi)
---

## 1. Description
	This is a weather data collection applicatopn project.
	Datas will be collected from weather APIs such as OpenWeatherAPI WeatherAPI
### 1.1. Current State
#### 1.1.1. Client HTTP/Server
	- Get datas London's weather datas from `OpenWeatherAPI` every 10 minutes
### 1.2. Current Goal
	The current is two have all elements working on a simple example of weather datas.
	- Server will get current temperature in Paris every n minutes
	- Datas will be stored in a single SQLite database
	- Client will ask for datas form the last hour
	- Client will display those datas in a list
#### 1.2.1. Improvements
	- Client will display datas in a graph
	- Client will be able to choose the time interval

## 2. Sub-projects
This project got two sub-project
### 2.1. Weather_Station_Client

	Client of the `Weather Station` Project it will request weather datas from the server and display in a graphic IHM.
	It will have two main part :
    - TCP Client
    - GUI
#### 2.1.1. Weather_Station_Client Classes

| Classes              | Description                                                                                      | Parent      |
| :------------------- | :----------------------------------------------------------------------------------------------- | :---------- |
| ClientTCP            | Application Clien                                                                                | QObject     |
| JSONParser           | Parser for json formated datas                                                                   | None        |
| WeatherData          | Class for weather datas                                                                          | None        |
| WeatherStationConfig | Manage client configuration                                                                      | None        |
| MainWindow           | define the client GUI                                                                            | QMainWindow |
| WeatherDataMap       | Manage result from request, emit signal when updated  	                                          | QObject     |

### 2.2. Weather_Station_Server
	Server of the `Weather Station` Project it will get weather datas from weather APIs and store it in a SQLite database. It will also provides access to the stored datas to its clients.
	It will have three main part :
    - TCP Server
    - HTTP Client
    - IHM
#### 2.2.1. Weather_Station_Server Classes

| Classes              | Description                                                                                      | Parent  |
| :------------------- | :----------------------------------------------------------------------------------------------- | :------ |
| ClientHTTP           | Http client class. Collect weather datas from a weatherAPI and store result in a SQLite database | QObject |
| DatabaseManager      | Manage database operations                                                                       | None    |
| JSONParser           | Parser for json formated datas                                                                   | None    |
| ServerTCP            | Application Server                                                                               | QObject |
| WeatherData          | Class for weather datas                                                                          | None    |
| WeatherStationConfig | Manage server configuration                                                                      | None    |

### 2.3. ApiDataToJson
	Small dll containing a function Parsing datas recieved from OpenWeatherAPI to the Application JSON Format

## 3. Protocol
	All comminication will be done in JSON
### 3.1. Client Data Frame
	All client frame will have cmd and params fields
#### Connection Data Frame <!-- omit in toc -->
		
```json
{
	"cmd":"connect",
	"params":null
}
```

#### request Data Frame <!-- omit in toc -->
		
```json
{
	"cmd":"request",
	"params":{
		"time":{"from":<int>, "to":<int>},
		"cities":[<String>]
	}
}
```

### 3.2. Server Data Frame
	All server frame will have cmd and results
	cmd value will be the same as in the message recieved from client
#### 3.2.1. Connection Data Frame
		
```json
{
	"cmd":"connect",
	"results":<bool>
}
```

#### 3.2.2. request Data Frame
		
```json
{
	"cmd":"request",
	"results":[<WeatherData>]
}
```
## 4. Configuration

### 4.1. Settings
#### 4.1.1. HTTP Client
- Cities list
- timeout
  
#### 4.1.2. TCP Server
- TCP port
- Database
  - type
  - name
  - base path
  - extention

#### 4.1.3. TCP Client

## 5. Troubleshooting
- [x] TCP crash after recieving request results, may be linked to the cretion of the QStandardItemModel
	- Solution :  Switch to QTableWidget

## 6. To Do
### 6.1. TCP Client/Server
- [x] Get basic code for TCP Client/Server
  - [x] Simple request between Client/Server
  - [x] "Boite a coucou"
- [x] Get datas from server 
- [x] Add a SQLite database
- [ ] Implement protocol
  - [ ] All messages in json
  - [ ] Add Session UID
	
#### 6.1.1. TCP Client
- [x] Basic IHM
  - [x] Single button IHM (send TCP request on click)
  - [x] Single button + Table View
- [x] Display datas in a table view
- [x] Use parmeters from requests

#### 6.1.2. HTTP Client
- [x] Get Data from API
  - [x] Make Succesfull request from `https://www.random.org`
- [x] Polling for request
- [x] add Json Parser
- [x] get datas from mutiple cities
  - [x] do chained requests
  
#### 6.1.3. Configuration file
- [ ] Define content of configuration file
  - [x] TCP Server/HTTP Client
  - [x] TCP Client
- [x] Manage file through `QSetting`
  - [x] TCP Server/HTTP Client
  - [x] TCP Client 
  
#### 6.1.4. IHM
- [x] add Charts
- [x] add request configuration element
    - [x] periode selection
    - [x] city selection
- [ ] Add layouts
- [x] Init date fields
- [x] Init Select field
  - Currently init to all
- [x] Display units
- [x] Display human readable date in graph
- [x] Display human readable date in table

#### 6.1.5. Documentation
#### 6.1.6. TCP Protocol
- [ ] Complete protocol
- [ ] Add diagram

---

## 7. See Also
### 7.1. Weather APIs
#### 7.1.1. OpenWeatherAPI
- `https://openweathermap.org`
#### 7.1.2. WeatherAPI
- `https://www.weatherapi.com`

