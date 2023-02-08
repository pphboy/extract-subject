#ifndef ESUTIL_H
#define ESUTIL_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "createsubjectwindow.h"
#include "mainwindow.h"
#include "addonesubjectdetail.h"
#include "extractpaper.h"


class EsUtil
{
    static QSqlDatabase db;
public:
    EsUtil();
    static QString getCurrentFormatData();
    static CreateSubjectWindow *CreateSubjectWindow; // 存储其指针在这里方便使用
    static AddOneSubjectDetail *AddOneSubjectDetail;
    static ExtractPaper *ExtractPaper;
    static MainWindow *MainWindow;
private:
};


#endif // ESUTIL_H
