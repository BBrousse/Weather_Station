QT = core network sql

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        clienthttp.cpp \
        databasemanager.cpp \
        jsonparser.cpp \
        main.cpp \
        servertcp.cpp \
        weatherdata.cpp \
        weatherstationconfig.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    clienthttp.h \
    databasemanager.h \
    jsonparser.h \
    servertcp.h \
    weatherdata.h \
    weatherstationconfig.h
