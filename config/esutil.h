#ifndef ESUTIL_H
#define ESUTIL_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "createsubjectwindow.h"
#include "mainwindow.h"
#include "addonesubjectdetail.h"
#include "extractpaper.h"
#include <random>
#include <iostream>


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
    /**
     * @brief extract
     * @param len 需要的随机索引长度
     * @param size 需要的随机索引的最大值
     * @return 返回一个随机索引值
     */
    static QVector<int> extract(int len,int size);
private:
};


#endif // ESUTIL_H
