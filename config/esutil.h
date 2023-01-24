#ifndef ESUTIL_H
#define ESUTIL_H

#include <QString>
#include <QSqlDatabase>

class EsUtil
{
public:
    static QSqlDatabase db;
    EsUtil();
    static QString getCurrentFormatData();
};

#endif // ESUTIL_H
