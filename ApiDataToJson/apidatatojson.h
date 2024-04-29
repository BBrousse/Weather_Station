#ifndef APIDATATOJSON_H
#define APIDATATOJSON_H

#include <QtCore/qglobal.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#if defined(APIDATATOJSON_LIBRARY)
#define APIDATATOJSON_EXPORT Q_DECL_EXPORT
#else
#define APIDATATOJSON_EXPORT Q_DECL_IMPORT
#endif


extern "C" APIDATATOJSON_EXPORT QJsonObject apiToDataToJSON(QJsonObject  const &api_json);

#endif // APIDATATOJSON_H

