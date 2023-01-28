#ifndef ESUTIL_H
#define ESUTIL_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "createsubjectwindow.h"
#include "addonesubjectdetail.h"

class EsUtil
{
    static QSqlDatabase db;
public:
    EsUtil();
    static QString getCurrentFormatData();
    static CreateSubjectWindow *CreateSubjectWindow; // 存储其指针在这里方便使用
    static AddOneSubjectDetail *AddOneSubjectDetail;
private:
};


#endif // ESUTIL_H
