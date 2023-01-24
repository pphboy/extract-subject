#ifndef SUBJECTSERVICE_H
#define SUBJECTSERVICE_H

#include <QSqlQuery>
#include <QString>
#include "daoconfig.h"

class SubjectService
{
public:
    SubjectService();
    bool addSubject(QString name); // 添加科目
    bool addCategory(QString name,int subjectId); // 添加分类
private:
    QSqlQuery *query;

};

#endif // SUBJECTSERVICE_H
