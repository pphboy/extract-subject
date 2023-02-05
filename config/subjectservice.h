#ifndef SUBJECTSERVICE_H
#define SUBJECTSERVICE_H

#include <QSqlQuery>
#include <QString>
#include "daoconfig.h"
#include "pojo/subject.h"

class SubjectService
{
public:
    SubjectService();
    bool addSubject(QString name); // 添加科目
    bool addCategory(QString name,int subjectId); // 添加分类
    bool addSubjectTask(QString title, QString answer,int categoryId);
    bool addTask(QString t_title,QString questionHtml, QString answerHtml, int categoryId, QString textContent);
    Subject * getSubjectById(int sid);
private:
    QSqlQuery *query;

};

#endif // SUBJECTSERVICE_H
