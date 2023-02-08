#include "esutil.h"
#include <ctime>
#include <QDebug>

using namespace std;

// 初始化指针
AddOneSubjectDetail* EsUtil::AddOneSubjectDetail = nullptr;
CreateSubjectWindow* EsUtil::CreateSubjectWindow = nullptr;
MainWindow* EsUtil::MainWindow = nullptr;
ExtractPaper* EsUtil::ExtractPaper = nullptr;
SubjectService* EsUtil::subjectService =nullptr;

EsUtil::EsUtil()
{
}

QString EsUtil::getCurrentFormatData()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);
    QString dateStr = QString("%1-%2-%3 %4:%5")
            .arg(localTime->tm_year+1900).arg(localTime->tm_mon+1).arg(localTime->tm_yday,2,10, QChar('0')).arg(localTime->tm_hour,2,10,QChar('0')).arg(localTime->tm_min,2,10,QChar('0'));
//    qDebug()  << "GetCurrentTime:"  << dateStr ;
    return dateStr;
}

default_random_engine e;
QVector<int> EsUtil::extract(int len, int size)
{
    uniform_int_distribution<int> u(0,size -1);

    QVector<int> vic;
    bool exist = false;

    cout << "[ ";
    while(vic.size() != len){
        int num = lround(u(e));
        for(auto a: vic){
            if(a == num){
                exist = true;
            }
        }
        if(!exist){
            vic.push_back(num);
            cout << num << ((vic.size() == len ) ? " ":",");
        }
        exist=false; // 每次执行完后需要初始化
    }
    cout << "]"<< endl;

    return vic;
}


