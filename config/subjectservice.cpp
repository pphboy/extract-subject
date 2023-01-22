#include "subjectservice.h"
#include <QDebug>
#include <QSqlQuery>

SubjectService::SubjectService()
{

}

bool SubjectService::addSubject(QString name)
{

    qDebug() << "添加科目：" << name;
}

bool SubjectService::addCategory(QString name, int subjectId)
{

}
