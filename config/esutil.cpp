#include "esutil.h"
#include <ctime>
#include <QDebug>

// 初始化指针
AddOneSubjectDetail* EsUtil::AddOneSubjectDetail = nullptr;
CreateSubjectWindow* EsUtil::CreateSubjectWindow = nullptr;
MainWindow* EsUtil::MainWindow = nullptr;
ExtractPaper* EsUtil::ExtractPaper = nullptr;

EsUtil::EsUtil()
{
}

QString EsUtil::getCurrentFormatData()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);
    QString dateStr = QString("%1-%2-%3 %4:%5")
            .arg(localTime->tm_year+1900).arg(localTime->tm_mon+1).arg(localTime->tm_yday,2,10, QChar('0')).arg(localTime->tm_hour,2,10,QChar('0')).arg(localTime->tm_min,2,10,QChar('0'));

    qDebug()  << "GetCurrentTime:"  << dateStr ;

    return dateStr;
}




